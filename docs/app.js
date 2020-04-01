var firebaseConfig = {
  apiKey: "AIzaSyDCxGMCgpOSBdunaZbh85PKmy8fZX_2Gzk",
  authDomain: "vip-auglib.firebaseapp.com",
  databaseURL: "https://vip-auglib.firebaseio.com",
  projectId: "vip-auglib",
  storageBucket: "vip-auglib.appspot.com",
  messagingSenderId: "592365426685",
  appId: "1:592365426685:web:0fe5c8d820c869bc70eb94",
  measurementId: "G-M6WY55M944"
};
// Initialize Firebase
firebase.initializeApp(firebaseConfig);
var firestore = firebase.firestore();

const readTest = document.querySelector('#read');

readTest.addEventListener("click", function(){
  firestore.collection("libserv").get().then((querySnapshot) => {
      querySnapshot.forEach((doc) => {
          console.log(doc.data());
      });
  });
});