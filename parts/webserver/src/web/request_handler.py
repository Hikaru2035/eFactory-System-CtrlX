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
from app.aws_publisher import AWSPublisher

data_layer: app.datalayer.DataLayer
aws_publisher = None

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
        
        # Image mp4
        if self.path.endswith(".mp4"):
            self.send_file_response('video/mp4')
            return
        
        # CSS
        if self.path.endswith(".css"):
            self.send_file_response('text/css')
            return

        # API DATA
        if self.path.startswith("/python-webserver/api/data"):

            parsedUrl = parse_qs(urlparse(self.path).query)
            token = ''
            if 'token' in parsedUrl:
                token = parsedUrl['token'][0]

            scopes_list = ["rexroth-device.all.rwx",
                        "rexroth-python-webserver.web.r", 
                        "rexroth-python-webserver.web.rw"]
            permissions_json = web.web_token.check_permissions(token, scopes_list)

            if permissions_json is None:
                self.send_response_and_header(401, 'application/json')
                self.wfile.write(b'{"error": "invalid token"}')
                return
            
            def extract_enum_value(enum_dict):
                if isinstance(enum_dict, dict) and len(enum_dict) > 0:
                    return list(enum_dict.values())[0]
                return str(enum_dict)
            
            # ------------------------- AVG FAC A+B -------------------------
            result, avg_availability_val    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeAvailAverage")
            result, avg_performance_val     = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeePerfAverage")
            result, avg_quality_val         = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeQualAverage")
            result, avg_oee_val             = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeCombinedAverage")
            result, avg_temp_val            = data_layer.read_node("plc/app/Application/sym/PLC_PRG/tempAverage")
            result, avg_humidity_val        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/humidityAverage")

            result, avg_schedule1_val        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/Schedule1")
            result, avg_schedule2_val        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/Schedule2")
            result, avg_schedule3_val        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/Schedule3")
            result, avg_schedule4_val        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/Schedule4")
            result, avg_schedule5_val        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/Schedule5")
            result, avg_schedule6_val        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/Schedule6")
            result, avg_schedule7_val        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/Schedule7")

            result, avg_pos_x_val            = data_layer.read_node("plc/app/Application/sym/PLC_PRG/Pos_X")
            result, avg_pos_y_val            = data_layer.read_node("plc/app/Application/sym/PLC_PRG/Pos_Y")
            result, avg_pos_z_val            = data_layer.read_node("plc/app/Application/sym/PLC_PRG/Pos_Z")
            
            result, avg_cloud_connection_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/cloudConnection")
            result, avg_cloud_enable_val      = data_layer.read_node("plc/app/Application/sym/PLC_PRG/cloudEnable")
            result, avg_data_enable_val       = data_layer.read_node("plc/app/Application/sym/PLC_PRG/dataEnable")

            result, avg_cloud_connected     = data_layer.read_node("plc/app/Application/sym/PLC_PRG/cloudConnected")
            result, avg_cloud_connecting    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/cloudConnecting")
            result, avg_cloud_error         = data_layer.read_node("plc/app/Application/sym/PLC_PRG/cloudError")
            
            result, avg_cloud_broker_val    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/cloudBroker")
            result, avg_cloud_ip_address    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/cloudIpAddress")
            result, avg_cloud_protocol      = data_layer.read_node("plc/app/Application/sym/PLC_PRG/cloudProtocol")
            result, avg_cloud_region        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/cloudRegion")
            result, avg_last_sync_timestamp   = data_layer.read_node("plc/app/Application/sym/PLC_PRG/lastSyncTimestamp")

            result, avg_time_counter_val     = data_layer.read_node("plc/app/Application/sym/PLC_PRG/timeCounter")
            result, avg_time_cycle_val       = data_layer.read_node("plc/app/Application/sym/PLC_PRG/timeCycle")
            result, avg_user_level_val       = data_layer.read_node("plc/app/Application/sym/PLC_PRG/userLevel")
            result, avg_user_name_val        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/userName")

            # ------------------------- FACTORY A -------------------------
            result, facA_availability_val   = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeAvail1")
            result, facA_performance_val    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeePerf1")
            result, facA_quality_val        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeQual1")
            result, facA_oee_val            = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeTotal1")
            
            result, facA_temp_outside_val   = data_layer.read_node("plc/app/Application/sym/PLC_PRG/tempOutside1")
            result, facA_temp_inside_val    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/tempInside1")
            result, facA_temp_avg_val       = data_layer.read_node("plc/app/Application/sym/PLC_PRG/tempAverage1")
            result, facA_humid_inside_val   = data_layer.read_node("plc/app/Application/sym/PLC_PRG/humidityInside1")
            result, facA_humid_outside_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/humidityOutside1")
            result, facA_humid_avg_val      = data_layer.read_node("plc/app/Application/sym/PLC_PRG/humidityAverage1")

            result, facA_servo1_temp_val    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoTemp1")
            result, facA_servo1_pos_val     = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoPos1")
            result, facA_servo1_status_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoStatus1")
            result, facA_servo2_temp_val    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoTemp2")
            result, facA_servo2_pos_val     = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoPos2")
            result, facA_servo2_status_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoStatus2")
            
            result, facA_sensor1_status_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorStatus1")
            result, facA_sensor2_status_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorStatus2")
            result, facA_sensor1_disInPos_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorDistInPos1")
            result, facA_sensor2_disInPos_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorDistInPos2")
            result, facA_driver_status_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/driverStatus1")

            result, facA_sensor1_temp_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorTemp1")
            result, facA_sensor2_temp_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorTemp2")
            result, facA_controller1_status_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/controllerStatus1")
            result, facA_controller1_temp_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/controllerTemp1")
            result, facA_controller1_usage_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/controllerUsage1")
            result, facA_driver_current1_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/driverCurrent1")
            result, facA_driver_temp1_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/driverTemp1")

             # ------------------------- FACTORY B -------------------------
            result, facB_availability_val   = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeAvail2")
            result, facB_performance_val    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeePerf2")
            result, facB_quality_val        = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeQual2")
            result, facB_oee_val            = data_layer.read_node("plc/app/Application/sym/PLC_PRG/oeeTotal2")
            
            result, facB_temp_outside_val   = data_layer.read_node("plc/app/Application/sym/PLC_PRG/tempInside2")
            result, facB_temp_inside_val    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/tempOutside2")
            result, facB_temp_avg_val       = data_layer.read_node("plc/app/Application/sym/PLC_PRG/tempAverage2")
            result, facB_humid_inside_val   = data_layer.read_node("plc/app/Application/sym/PLC_PRG/humidityInside2")
            result, facB_humid_outside_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/humidityOutside2")
            result, facB_humid_avg_val      = data_layer.read_node("plc/app/Application/sym/PLC_PRG/humidityAverage2")

            result, facB_servo1_temp_val    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoTemp3")
            result, facB_servo1_pos_val     = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoPos3")
            result, facB_servo1_status_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoStatus3")
            result, facB_servo2_temp_val    = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoTemp4")
            result, facB_servo2_pos_val     = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoPos4")
            result, facB_servo2_status_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/servoStatus4")
            
            result, facB_sensor1_status_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorStatus3")
            result, facB_sensor2_status_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorStatus4")
            result, facB_sensor1_disInPos_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorDistInPos3")
            result, facB_sensor2_disInPos_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorDistInPos4")
            result, facB_driver_status_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/driverStatus2")

            result, facB_sensor3_temp_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorTemp3")
            result, facB_sensor4_temp_val = data_layer.read_node("plc/app/Application/sym/PLC_PRG/sensorTemp4")
            result, facB_controller2_status_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/controllerStatus2")
            result, facB_controller2_temp_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/controllerTemp2")
            result, facB_controller2_usage_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/controllerUsage2")
            result, facB_driver_current2_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/driverCurrent2")
            result, facB_driver_temp2_val  = data_layer.read_node("plc/app/Application/sym/PLC_PRG/driverTemp2")

            # ------------------------- JSON RESPONSE -------------------------
            response = {
                # ================= AVG (Factory A + B) =================
                "avg": {
                    "availability"  : round(avg_availability_val),
                    "performance"   : round(avg_performance_val),
                    "quality"       : round(avg_quality_val),
                    "oee"           : round(avg_oee_val),
                    "temperature"   : round(avg_temp_val, 1),
                    "humidity"      : round(avg_humidity_val, 1),

                    "schedule1"     : round(avg_schedule1_val, 1),
                    "schedule2"     : round(avg_schedule2_val, 1),
                    "schedule3"     : round(avg_schedule3_val, 1),
                    "schedule4"     : round(avg_schedule4_val, 1),
                    "schedule5"     : round(avg_schedule5_val, 1),
                    "schedule6"     : round(avg_schedule6_val, 1),
                    "schedule7"     : round(avg_schedule7_val, 1),

                    "position": {
                        "x": round(avg_pos_x_val, 2),
                        "y": round(avg_pos_y_val, 2),
                        "z": round(avg_pos_z_val, 2)
                    },
                    
                    "cloud": {
                        "connection": bool(avg_cloud_connection_val),
                        "enable": bool(avg_cloud_enable_val),
                        "dataEnable": bool(avg_data_enable_val),

                        "status": {
                            "connected": bool(avg_cloud_connected),
                            "connecting": bool(avg_cloud_connecting),
                            "error": bool(avg_cloud_error)
                        },

                        "info": {
                            "broker": avg_cloud_broker_val,
                            "region": avg_cloud_region,
                            "protocol": avg_cloud_protocol,
                            "ipAddress": avg_cloud_ip_address,
                            "lastSync": avg_last_sync_timestamp
                        }
                    },

                    "system": {
                        "timeCounter": avg_time_counter_val,
                        "timeCycle": avg_time_cycle_val
                    },

                    "user": {
                        "level": avg_user_level_val,
                        "name": avg_user_name_val
                    }
                },

                # ================= FACTORY A =================
                "factoryA": {
                    "oee": {
                        "availability"  : round(facA_availability_val),
                        "performance"   : round(facA_performance_val),
                        "quality"       : round(facA_quality_val),
                        "total"         : round(facA_oee_val)
                    },
                    "environment": {
                        "temperature": {
                            "inside": round(facA_temp_inside_val, 1),
                            "outside": round(facA_temp_outside_val, 1),
                            "average": round(facA_temp_avg_val, 1)
                        },
                        "humidity": {
                            "inside": round(facA_humid_inside_val, 1),
                            "outside": round(facA_humid_outside_val, 1),
                            "average": round(facA_humid_avg_val, 1)
                        }
                    },
                    "machines": {
                        "servo1": {
                            "temperature": round(facA_servo1_temp_val, 1),
                            "position": round(facA_servo1_pos_val, 1),
                            "status": extract_enum_value(facA_servo1_status_val)
                        },
                        "servo2": {
                            "temperature": round(facA_servo2_temp_val, 1),
                            "position": round(facA_servo2_pos_val, 1),
                            "status": extract_enum_value(facA_servo2_status_val)
                        }
                    },
                    "status": {
                        "sensor1": extract_enum_value(facA_sensor1_status_val),
                        "sensor2": extract_enum_value(facA_sensor2_status_val),
                        "driver": extract_enum_value(facA_driver_status_val)
                    },
                    "distance": {
                        "sensor1": facA_sensor1_disInPos_val,
                        "sensor2": facA_sensor2_disInPos_val
                    },
                   
                    "devices": {
                        "sensors": {
                            "sensor1": {
                                "temperature": round(facA_sensor1_temp_val, 1)
                            },
                            "sensor2": {
                                "temperature": round(facA_sensor2_temp_val, 1)
                            }
                        },
                        "controller": {
                            "status": extract_enum_value(facA_controller1_status_val),
                            "temperature": round(facA_controller1_temp_val, 1),
                            "usage": round(facA_controller1_usage_val, 1)
                        },
                        "driver": {
                            "current": round(facA_driver_current1_val, 1),
                            "temperature": round(facA_driver_temp1_val, 1)
                        }
                    }

                },

                # ================= FACTORY B =================
                "factoryB": {
                    "oee": {
                        "availability": round(facB_availability_val),
                        "performance": round(facB_performance_val),
                        "quality": round(facB_quality_val),
                        "total": round(facB_oee_val)
                    },
                    "environment": {
                        "temperature": {
                            "inside": round(facB_temp_inside_val, 1),
                            "outside": round(facB_temp_outside_val, 1),
                            "average": round(facB_temp_avg_val, 1)
                        },
                        "humidity": {
                            "inside": round(facB_humid_inside_val, 1),
                            "outside": round(facB_humid_outside_val, 1),
                            "average": round(facB_humid_avg_val, 1)
                        }
                    },
                    "machines": {
                        "servo1": {
                            "temperature": round(facB_servo1_temp_val, 1),
                            "position": round(facB_servo1_pos_val, 1),
                            "status": extract_enum_value(facB_servo1_status_val)
                        },
                        "servo2": {
                            "temperature": round(facB_servo2_temp_val, 1),
                            "position": round(facB_servo2_pos_val, 1),
                            "status": extract_enum_value(facB_servo2_status_val)
                        }
                    },
                    "status": {
                        "sensor1": extract_enum_value(facB_sensor1_status_val),
                        "sensor2": extract_enum_value(facB_sensor2_status_val),
                        "driver": extract_enum_value(facB_driver_status_val)
                    },
                    "distance": {
                        "sensor1": facB_sensor1_disInPos_val,
                        "sensor2": facB_sensor2_disInPos_val
                    },

                    "devices": {
                        "sensors": {
                            "sensor1": {
                                "temperature": round(facB_sensor3_temp_val, 1)
                            },
                            "sensor2": {
                                "temperature": round(facB_sensor4_temp_val, 1)
                            }
                        },
                        "controller": {
                            "status": extract_enum_value(facB_controller2_status_val),
                            "temperature": round(facB_controller2_temp_val, 1),
                            "usage": round(facB_controller2_usage_val, 1)
                        },
                        "driver": {
                            "current": round(facB_driver_current2_val, 1),
                            "temperature": round(facB_driver_temp2_val, 1)
                        }
                    }

                }
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
