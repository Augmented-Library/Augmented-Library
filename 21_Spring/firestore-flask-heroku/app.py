# app.py
from flask import Flask, request, jsonify, render_template
import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore

#Use a service account
cred = credentials.Certificate("vip-auglib-firebase-adminsdk-olvnl-3ee21046f9.json")
firebase_admin.initialize_app(cred)
db = firestore.client()

app = Flask(__name__)
#app.config['ENV'] = 'development'
#app.config['DEBUG'] = True
#app.config['TESTING'] = True

# A welcome message to test our server
@app.route('/')
def hello():
    doc_ref = db.collection(u"flyers").document(u"heroku_flask_doc")
    doc = doc_ref.get()
    doc_dict = doc.to_dict()
    #print(doc_dict)
    #print(f'Document data: {doc.to_dict()}')
    return render_template("home.html", data=doc_dict.items())

@app.route('/updateFlyer', methods=["POST"])
def updateFlyer():
    data = request.form
    db.collection(u"flyers").document(u"heroku_flask_doc").set(data)
    return render_template("home.html", data=data.items(), note="success")
    
if __name__ == '__main__':
    # Threaded option to enable multiple instances for multiple user access support
    app.run("127.0.0.1", port=5000)