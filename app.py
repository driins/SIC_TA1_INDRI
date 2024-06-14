from flask import Flask, request, jsonify

app = Flask(__name__)

# Global list untuk store data temperature dan kelembapan
data = []

@app.route("/")
def entry_point():
    welcome_message = (
        "Technical Assignment 1 - SIC Batch 5<br>"
        "======================================<br><br>"
        "WELCOME TO API KELOMPOK 24 SIC Batch 5<br><br>" 
        "Anggota kelompok 24: <br>"
        "1. Indri Windriasari <br>"
        "2. Ali Astra Mikail <br>"
        "3. Ginanjar Aditiya Prianata <br>"
        "4. Prayoga Setiawan <br><br>"
        "Tujuan API ini adalah untuk menyimpan dan mengakses data temperatur dan kelembapan yang dikirimkan oleh sensor DHT11.<br><br>"
        "Instruksi penggunaan:<br>"
        "1). Jalankan app.py dengan VSCode <br>" 
        "2). Catat servel url yang running di terminal <br>"
        "3). Buka Arduino IDE, setel server_url pada file sic_ta1.ino ke server url yang muncul di terminal VSCode <br>"
        "4). Compile dan upload sic_ta1.ino ke ESP32 <br>"
        "5). Cek serial monitor untuk mengetahui tidak ada error dan semuanya telah terkoneksi dengan baik <br>"
        "6). Untuk melihat hasil, gunakan endpoint 'your-server-url:port/sensor/data' <br>")
    return welcome_message

@app.route("/sensor/data", methods=["POST"])
def post_data():
    json_data = request.get_json()
    temperature = json_data.get("temperature")
    kelembapan = json_data.get("humidity")  

    # Store data
    subData = {"temperature": temperature, "humidity": kelembapan}
    data.append(subData)
    return 'berhasil disimpan ke server', 201

@app.route("/sensor/data", methods=["GET"])
def get_data():
    return jsonify(data)

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=True)
