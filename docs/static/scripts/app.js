var firestore = firebase.firestore();
var currentPathname = window.location.pathname;

function readDB(serviceTable){
  var cols = ["name", "description", "location"];

  firestore.collection('libserv').get().then((querySnapshot) => {
    querySnapshot.forEach((doc) => {
      var row = serviceTable.insertRow();
      var data = doc.data();
      for(let i = 0; i < 3; i++){
        var cell = row.insertCell();
        var text = document.createTextNode(data[cols[i]]);
        cell.append(text);
      };
    });
  });
  serviceTable.style.visibility = 'visible';
}

function writeDB(){
  var addName = document.querySelector('#addSvcName');
  var addDesc = document.querySelector('#addSvcDesc');
  var addLoc = document.querySelector('#addSvcLoc');

  //need to do further sanitization
  firestore.collection('libserv').add({
    name: addName.value.trim(),
    description: addDesc.value.trim(),
    location: addLoc.value.trim()
  })
  .then((docRef) => {
    console.log("Document written with ID: ", docRef.id);

    var newRowData = [addName, addDesc, addLoc];
    var serviceTable = document.querySelector('#serviceTable');
    var row = serviceTable.insertRow();
    for (let i = 0; i < 3; i++){
      var cell = row.insertCell();
      var text = document.createTextNode(newRowData[i].value);
      cell.append(text);
      newRowData[i].value = '';
    };
  })
  .catch((error) => {
    console.error("Error adding document: ", error);
  });
}

if (currentPathname == '/Augmented-Library/') {

  //Add data from Firebase to table and then display table
  var serviceTable = document.querySelector('#serviceTable');
  var readFlag = false;
  if (!readFlag){
    window.addEventListener('load',readDB(serviceTable));
  }

  //Add data to Firebase
  var submitButton = document.querySelector('#addSvcBtn');
  submitButton.addEventListener('click',writeDB);
}