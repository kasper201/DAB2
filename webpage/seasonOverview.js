var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        if (this.responseText.trim() !== "") {
            let response = JSON.parse(this.responseText);
            let timeline = Array.isArray(response) ? response : [response];
            let timelineContainer = document.querySelector('.Name');

            console.log(timeline);

            // Create a table element
            let table = document.createElement('table');

            // Define the table headers
            let headers = ['Season', 'Circuit Name', 'Location', 'Date', 'Points awarded', 'Race Type', 'Pole Position'];
            let tableNames = ['season', 'circuitNaam', 'locatie', 'datum', 'total_points', 'racetype', 'polePositionCoureur'];
            let tr = document.createElement('tr');
                tr.style.color = 'white';
            headers.forEach(headers => {
                let th = document.createElement('th');
                th.textContent = headers;
                tr.appendChild(th);
            });
            table.appendChild(tr);

            // Loop through the timeline array and create a new row for each item
            timeline.forEach(item => {
                let tr = document.createElement('tr');

                // If the race type is 'sprint', add a class to the row
                if (item['racetype'] === 'Normal') {
                    tr.style.backgroundColor = '#c90000';
                } else {
                    tr.style.backgroundColor = '#d5d5d5';
                }

                // For each item, create a new cell for each property and append it to the row
                tableNames.forEach(tableNames => {
                    let td = document.createElement('td');
                    // Add this if you feel like it but it doesn't work yet
                    // if(tableNames === 'circuitNaam'){
                    //     localStorage.setItem('search', item[tableNames]);
                    //     td.innerHTML = '<a href="./circuit.html">' + item[tableNames] + '</a>';
                    // } else
                    {
                        td.textContent = item[tableNames];
                    }
                    tr.appendChild(td);
                });

                // Append the row to the table
                table.appendChild(tr);
            });

            // Append the table to the timelineContainer
            timelineContainer.appendChild(table);
        } else {
        console.log("Empty response received");
        console.log("response: " + this.responseText);
    }
    } else if (this.status === 500) {
        console.log("Error: " + this.status);
        console.log("response: " + this.responseText);
        console.log("State: " + this.readyState);
    } else if (this.status === 404) {
        window.location.href = '../404.html';
    } else {
        console.log("Error: " + this.status);
        console.log("State: " + this.readyState);
    }
};

// Send the request
console.log("Sending request");
xhttp.open("GET", "./php/getTimeline.php", true);
xhttp.send();