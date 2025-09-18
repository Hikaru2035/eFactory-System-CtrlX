# SPDX-FileCopyrightText: Bosch Rexroth AG
#
# SPDX-License-Identifier: MIT

import os
import traceback

import http.server

import web.web_token

from urllib.parse import unquote, parse_qs, urlparse
from json import dumps, loads

import app.datalayer

data_layer: app.datalayer.DataLayer


class RequestHandler(http.server.BaseHTTPRequestHandler):
    # Form parameters saved server side
    # "datalayer/subscriptions/settings"
    # "framework/metrics/system/cpu-utilisation-percent"
    readPath = "datalayer/subscriptions/settings"
    readValue = ""
    readResult = ""
    writePath = "sdk/py/provider/alldata/dynamic/int64"
    writeValue = "123456789"
    writeResult = ""

    def do_HEAD(self):
        return

    def get_www_file_path(self, relative_path):
        # relative_path: 'www/xxx' or '/python-webserver/stylesheet.css'

        if len(relative_path) <= 0:
            relative_path = self.path

        print("get_www_file_path relative_path: %s", relative_path)

        rel_www_path = "/www/" + os.path.basename(relative_path)

        snap_path = os.getenv('SNAP')

        result_path = os.getcwd() + rel_www_path if snap_path is None else snap_path + rel_www_path

        print("get_www_file_path result_path:", result_path, flush=True)

        return result_path

    def send_response_and_header(self, response, content_type):
        self.send_response(response)

        self.send_header('Content-type', content_type)
        self.end_headers()

    def send_file_response(self, content_type, rel_path=""):
        path = self.get_www_file_path(rel_path)

        try:
            with open(path, "rb") as bufferedReader:
                self.send_response_and_header(200, content_type)
                self.wfile.write(bufferedReader.read())
        except Exception:
            print("EXCEPTION Opening and sending file:", path)
            print(traceback.format_exc(), flush=True)
            self.send_response_and_header(404, content_type)

    def send_html_file_response(self, rel_path=""):
        path = self.get_www_file_path(rel_path)
        content_type = 'text/html'

        try:
            with open(path) as bufferedReader:
                self.send_response_and_header(200, content_type)
                self.wfile.write(bytes(bufferedReader.read(), 'utf-8'))
        except Exception:
            print("EXCEPTION opening and sending file:", path)
            print(traceback.format_exc(), flush=True)
            self.send_response_and_header(404, content_type)

    def do_GET(self):
        # GET Requests from client
        print("GET", self.path, flush=True)

        # Attempt To Send Different Files
        if self.path.endswith(".png"):
            # https://www.w3schools.com/html/html_favicon.asp
            # A favicon is a small image displayed next to the page title in the browser tab.
            # Browsers are caching this file
            self.send_file_response('image/png')
            return

        # Image jpg
        if self.path.endswith(".jpg"):
            self.send_file_response('image/jpg')
            return

        # Image gif
        if self.path.endswith(".gif"):
            self.send_file_response('image/gif')
            return

        # CSS
        if self.path.endswith(".css"):
            self.send_file_response('text/css')
            return

        # API
        if self.path.startswith("/python-webserver/api/data"):

            parsedUrl = parse_qs(urlparse(self.path).query)
            token = ''
            if 'token' in parsedUrl:
                token = parsedUrl['token'][0]

            # check quyền
            scopes_list = ["rexroth-device.all.rwx",
                        "rexroth-python-webserver.web.r", 
                        "rexroth-python-webserver.web.rw"]
            permissions_json = web.web_token.check_permissions(token, scopes_list)

            if permissions_json is None:
                self.send_response_and_header(401, 'application/json')
                self.wfile.write(b'{"error": "invalid token"}')
                return

            # Đọc từ DataLayer
            result, availability_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeAvail1")
            result, performance_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeePerf1")
            result, quality_val     = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeQual1")
            result, total_val     = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeTotal1")
            result, temp_val       = data_layer.read_node("plc/app/Application/sym/PLC_PRG/tempInside1")
            result, humidity_val   = data_layer.read_node("plc/app/Application/sym/PLC_PRG/humidityInside1")


            # Gửi JSON về client
            response = {
                "availability": round(availability_val),
                "performance": round(performance_val),
                "quality": round(quality_val),
                "oee": round(total_val),
                "temperature": round(temp_val),
                "humidity": round(humidity_val)
            }


            import json
            self.send_response_and_header(200, 'application/json')
            self.wfile.write(json.dumps(response).encode("utf-8"))
            return
        
        # HTML
        if self.path.startswith("/python-webserver"):

            # Parsing bearer token from url
            parsedUrl = parse_qs(urlparse(self.path).query)
            token = ''
            if 'token' in parsedUrl:
                token = parsedUrl['token'][0]

            # check user permissions of token
            scopes_list = ["rexroth-device.all.rwx",
                           "rexroth-python-webserver.web.r", 
                           "rexroth-python-webserver.web.rw"]
            permissions_json = web.web_token.check_permissions(token, scopes_list)

            # if token is invalid
            if permissions_json is None:

                # self.write_www_file(content_type='text/html', rel_path='www/html-invalid-token.html')
                self.send_html_file_response(rel_path='www/invalid-token.html')
                return

            self.send_response_and_header(200, 'text/html')
                
            # --- Determine which file to serve ---
            # Case 1: entrypoint "/python-webserver?token=..."
            if self.path.startswith("/python-webserver?"):
                rel_file = "index.html"
            else:
                # Case 2: "/python-webserver/xxx.html?token=..."
                rel_file = self.path.split("/python-webserver/")[-1].split("?")[0]
                if rel_file.strip() == "":
                    rel_file = "index.html"

            # --- Read file ---
            path = self.get_www_file_path("/www/" + rel_file)
            try:
                with open(path, encoding="utf-8") as f:
                    htmlX = f.read()
            except Exception as e:
                print("Error loading file:", path, e, flush=True)
                self.send_html_file_response(rel_path="www/404.html")
                return

            # Replace placeholders
            htmlX = htmlX.replace("$(token)", token)

            # Enable/disable HTML objects according permissions
            permissions_read = permissions_json['rexroth-device.all.rwx'] or permissions_json[
                'rexroth-python-webserver.web.rw'] or permissions_json['rexroth-python-webserver.web.r']
            permissions_write = permissions_json['rexroth-device.all.rwx'] or permissions_json['rexroth-python-webserver.web.rw']
            htmlX = htmlX.replace(
                '$(permissions_read_text)', '' if permissions_read else "'disabled'")  # Text must be surrounded by ' '
            htmlX = htmlX.replace(
                '$(permissions_write_text)', '' if permissions_write else "'disabled'")  # Text must be surrounded by ' '

            # Set read content
            htmlX = htmlX.replace('$(Server.readPath)',
                                  str(RequestHandler.readPath))
            htmlX = htmlX.replace('$(Server.readValue)',
                                  str(RequestHandler.readValue))
            htmlX = htmlX.replace('$(Server.readResult)',
                                  str(RequestHandler.readResult))

            htmlX = htmlX.replace('$(Server.writePath)',
                                  str(RequestHandler.writePath))
            htmlX = htmlX.replace('$(Server.writeValue)',
                                  str(RequestHandler.writeValue))
            htmlX = htmlX.replace('$(Server.writeResult)',
                                  str(RequestHandler.writeResult))

            # Show permissions: 'True' or 'False'
            htmlX = htmlX.replace('$(permissions_rwx)', str(
                permissions_json['rexroth-device.all.rwx']))
            htmlX = htmlX.replace('$(permissions_rw)', str(
                permissions_json['rexroth-python-webserver.web.rw']))
            htmlX = htmlX.replace('$(permissions_r)', str(
                permissions_json['rexroth-python-webserver.web.r']))
            
            # (giá trị mẫu, có thể lấy từ DataLayer hoặc DB)
            # Đọc Availability
            #result, availability_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeAvail1")
            # Đọc Performance
            #result, performance_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeePerf1")
            # Đọc Quality
            #result, quality_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeQual1")
            schedule_data = "[12, 19, 3, 5, 2, 3, 10, 15, 7, 8, 12, 14]"
            avg_temp = "65"
            avg_humidity = "45"
            error_rows = """
                <tr><td>1</td><td>Line 1</td><td>2025-09-05</td><td>Pending</td><td>50</td></tr>
                <tr><td>2</td><td>Line 2</td><td>2025-09-05</td><td>Resolved</td><td>20</td></tr>
            """

            # Thay placeholder trong HTML
            #htmlX = htmlX.replace("$(availability)", str(availability_val))
            #htmlX = htmlX.replace("$(performance)", str(performance_val))
            #htmlX = htmlX.replace("$(quality)", str(quality_val))
            htmlX = htmlX.replace("$(schedule_data)", schedule_data)
            htmlX = htmlX.replace("$(avg_temp)", avg_temp)
            htmlX = htmlX.replace("$(avg_humidity)", avg_humidity)
            htmlX = htmlX.replace("$(error_rows)", error_rows)

            self.wfile.write(htmlX.encode("utf-8"))
            return
        
        self.send_response(404)

    def do_POST(self):
        """do_POST
        """
        # Get the size of data
        content_length = int(self.headers['Content-Length'])
        content = self.rfile.read(content_length).decode("utf-8")
        post_data = unquote(content)
        json = dumps(parse_qs(post_data))
        data = loads(json)

        print("POST", str(data), flush=True)

        # Evaluate post data
        if data['submit'][0] == 'Read Value':

            if 'node' in data:
                RequestHandler.readPath = data['node'][0]

                # ctrlX Data Layer access
                RequestHandler.readResult, RequestHandler.readValue = data_layer.read_node(
                    RequestHandler.readPath)

            else:
                RequestHandler.readValue = ''
                RequestHandler.readResult = 'INVALID NODE'

        if data['submit'][0] == 'Write Value':

            if 'node' in data and 'value' in data:
                RequestHandler.writePath = data['node'][0]
                RequestHandler.writeValue = data['value'][0]

                # ctrlX Data Layer access
                RequestHandler.writeResult = data_layer.write_node(
                    RequestHandler.writePath, RequestHandler.writeValue)

            else:
                RequestHandler.writeValue = ''
                RequestHandler.writeResult = 'INVALID NODE'

        self.send_response(303)
        self.send_header('Content-type', 'text/html')
        self.send_header('Location', self.path)
        self.end_headers()
