var firestore = firebase.firestore();

var currentPathname = window.location.pathname;

if (currentPathname == '/Aug-Lib-Demo/') {

  //Add data from Firebase to table and then display table
  var serviceTable = document.querySelector('#serviceTable');
  var readFlag = false;
  if (!readFlag){
    window.addEventListener('load', function(){
      firestore.collection('libserv').get().then((querySnapshot) => {
        querySnapshot.forEach((doc) => {
          var row = serviceTable.insertRow();
          var data = doc.data();
          for(var item in data){
            var cell = row.insertCell();
            var text = document.createTextNode(data[item]);
            cell.append(text);
          };
        });
      });
      serviceTable.style.visibility = 'visible';
    });
  }

  //Add data to Firebase
  var addServiceForm = document.querySelector('#addService');
  var submitButton = document.querySelector('#addServicebtn');
  submitButton.addEventListener('click',function(){
    var name = addServiceForm.serviceName.value.trim();
    var description = addServiceForm.serviceDesc.value.trim();
    var location = addServiceForm.serviceLoc.value.trim();
    //need to do further sanitization
    if (name != '' && description != '' && location != ''){
      firestore.collection('libserv').add({
        Name: "Test Write 2",
        Description: "Test Write 2",
        Location: "Test Write 2"
      });
      console.log("Wrote to database");
    }
    else {
      console.log("Cannot have empty fields");
    }
  });
}