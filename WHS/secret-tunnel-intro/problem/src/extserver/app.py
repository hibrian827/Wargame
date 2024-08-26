from flask import Flask, request, render_template_string, jsonify, send_file
import pickle
import base64
import hashlib
import re
import json
import subprocess
import os
import tempfile

app = Flask(__name__)
app.config['DEBUG'] = True

SECRET_KEY = "very_secret_key_do_not_guess"

def verify_signature(data, signature):
    return hashlib.md5((data + SECRET_KEY).encode()).hexdigest() == signature

@app.route('/process', methods=['POST'])
def process_data():

    data = request.form.get('data')
    signature = request.form.get('signature')

    if not verify_signature(data, signature):
        return "Invalid signature", 400

    if isinstance(data, dict):
        return jsonify({"result": "Processed JSON data", "data": data})
    else:
        decoded = base64.b64decode(data)
        if b'pickle' in decoded.lower():
            return "Suspicious input detected", 400
        
        obj = pickle.loads(decoded)
        
        if isinstance(obj, dict) and 'template' in obj:
            if obj['template'].count('{') != obj['template'].count('}'):
                return "Invalid template", 400
            if re.search(r'(config|self|import|os|subprocess|popen)', obj['template'], re.I):
                return "Suspicious template detected", 400
            
            return render_template_string(obj['template'])
        else:
            return f"Processed data: {obj}"


@app.route('/get_file', methods=['POST'])
def get_file():
    filename = request.form.get('filename')
    
    if not re.match(r'^[a-zA-Z0-9_.-]+$', filename):
        return "Invalid filename", 400
    
    allowed_files = ['dari11.jpg', 'dari22.jpg', 'dari33.jpg']
    if filename not in allowed_files:
        return "File not allowed", 403
    
    with tempfile.NamedTemporaryFile(delete=False) as temp_file:
        temp_path = temp_file.name
    
    try:
        result = subprocess.run(['/home/appuser/scp_transfer.sh', f'/home/ctfuser/{filename}', temp_path], 
                                capture_output=True, text=True, timeout=30)
        
        if result.returncode != 0:
            return f"File transfer failed: {result.stderr}", 500
        
        return send_file(temp_path, as_attachment=True, attachment_filename=filename)
    
    except subprocess.TimeoutExpired:
        return "File transfer timed out", 500
    finally:
        os.unlink(temp_path)

@app.route("/", methods=["GET"])
def index():
    return "hello"

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8090, debug=True)