async function fetchOEE() {
  try {
    const urlParams = new URLSearchParams(window.location.search);
    const token = urlParams.get("token");

    let res = await fetch(`/python-webserver/api/oee?token=${token}`);
    let data = await res.json();

    document.getElementById("availability").textContent = data.availability;
    document.getElementById("performance").textContent  = data.performance;
    document.getElementById("quality").textContent      = data.quality;

  } catch (err) {
    console.error("Polling error:", err);
  }
}

// gọi mỗi 1 giây
setInterval(fetchOEE, 1000);