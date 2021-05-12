var firestore = firebase.firestore();
var currentPathname = window.location.pathname;

function readDB(serviceTable){
  var cols = ['name', 'description', 'location'];

  firestore.collection('libserv').get().then((querySnapshot) => {
    querySnapshot.forEach((doc) => {
      var row = serviceTable.insertRow();
      var data = doc.data();

      row.id = doc.id;

      for(let i = 0; i < 3; i++){
        var cell = row.insertCell();
        var text = document.createTextNode(data[cols[i]]);
        cell.append(text);
      };
      var cell = row.insertCell();
      //edit button
      var editButton = createEditButton();
      //remove button
      var rmButton = createRmButton();

      cell.append(editButton, rmButton);
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
    console.log('Document written with ID: ', docRef.id);

    var newRowData = [addName, addDesc, addLoc];
    var serviceTable = document.querySelector('#serviceTable');
    var row = serviceTable.insertRow();

    row.id = docRef.id;

    for (let i = 0; i < 3; i++){
      var cell = row.insertCell();
      var text = document.createTextNode(newRowData[i].value);
      cell.append(text);
      newRowData[i].value = '';
    };
    var cell = row.insertCell();
    //edit button
    var editButton = createEditButton();
    //remove button
    var rmButton = createRmButton();

    cell.append(editButton, rmButton);
  })
  .catch((error) => {
    console.error('Error adding document: ', error);
  });
}

function createEditButton(){
  var editButton = document.createElement('button');
  editButton.className = 'editBtn';
  editButton.innerHTML = 'Edit';
  editButton.addEventListener('click',editRow);
  return editButton;
}

function editRow(){
  var cols = ['Name', 'Description', 'Location'];

  var rowElement = this.parentElement.parentElement;
  var rowValues = rowElement.childNodes;
  var popup = document.querySelector('#edit-popup');
  popup.style.display = 'block';
  var popupBG = document.querySelector('#edit-popup-overlay');
  popupBG.style.display = 'block';

  var contents = document.querySelector('#edit-popup-contents');
  contents.name = rowElement.id;
  contents.innerHTML = '';
  for (let i = 0; i < 3; i++){
    var label = document.createElement('label');
    label.innerHTML = cols[i];
    var textInput = document.createElement('input');
    textInput.type = 'text';
    textInput.value = rowValues[i].innerHTML;
    contents.append(label);
    contents.append(textInput);
  };

  //var rowDoc = firestore.collection('libserv').doc(rowElement.id).get();
}

// Ugly code, doesn't update the table
function saveEdit(){
  var popup = document.querySelector('#edit-popup-contents');
  var popupContent = popup.childNodes;
  var newValues = [];
  for (let i = 0; i < popupContent.length; i++){
    if (popupContent[i].nodeName == "INPUT"){
      newValues.push(popupContent[i].value);
    }
  }

  firestore.collection('libserv').doc(popup.name).update({
    name: newValues[0],
    description: newValues[1],
    location: newValues[2]
  })
  .then(() => {
    console.log("Updated: ", popup.name);
    document.querySelector('#edit-popup-overlay').style.display = 'none';
    var tableRowItems = document.querySelector('#'+popup.name).childNodes;
    for (let i = 0; i < 3; i++){
      tableRowItems[i].innerHTML = newValues[i];
    }
  })
}

function cancelEdit(){
  var popup = document.querySelector('#edit-popup');
  popup.style.display = 'none';

  var popupBG = document.querySelector('#edit-popup-overlay');
  popupBG.style.display = 'none';
}

function createRmButton(){
  var rmButton = document.createElement('button');
  rmButton.className = 'removeBtn';
  rmButton.innerHTML = 'Remove';
  rmButton.addEventListener('click',removeRow);
  return rmButton;
}

function removeRow(){
  var rowElement = this.parentElement.parentElement;
  firestore.collection('libserv').doc(rowElement.id).delete().then(() => {
    console.log('Deleted document: ', rowElement.id);
    rowElement.remove();
  }).catch((error) => {
    console.error('Error deleting document: ', error);
  });
}

//-----------RUNS WHEN PAGE LOADS-----------
if (currentPathname == '/Augmented-Library/'){
  //Add data from Firebase to table and then display table
  var serviceTable = document.querySelector('#serviceTable');
  var readFlag = false;
  if (!readFlag){
    window.addEventListener('load',readDB(serviceTable));
  }

  //Add data to Firebase
  var submitButton = document.querySelector('#addSvcBtn');
  submitButton.addEventListener('click',writeDB);

  //Save edit data to Firebase
  var saveButton = document.querySelector('#saveBtn');
  saveButton.addEventListener('click',saveEdit);

  //Cancel edit data to Firebase
  var cancelButton = document.querySelector('#cancelBtn');
  cancelButton.addEventListener('click',cancelEdit);
}
