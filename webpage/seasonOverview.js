var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        if (this.responseText.trim() !== "") {
            let response = JSON.parse(this.responseText);
            let timeline = Array.isArray(response) ? response : [response];

            // log to console for debugging
            console.log(response);
        }
    }
};

//var urlParams = new URLSearchParams(window.location.search);

// Send the request
console.log("Sending request");
xhttp.open("GET", "php/getTimeline.php", true);