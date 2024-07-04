var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        if (this.responseText.trim() !== "") {
            let response = JSON.parse(this.responseText);
            let timeline = Array.isArray(response) ? response : [response];
            let timelineContainer = document.querySelector('.Name');

            console.log(response);

            // Create a table element
            let table = document.createElement('table');

            // Define the table headers
            let headers = ['Name', '', 'Team', 'Total points', 'First Places', 'Second Places', 'Third Places'];
            let tableNames = ['naam', 'nationalflag', 'team', 'Total points', 'First places', 'second places', 'third places'];
            let tr = document.createElement('tr');
            tr.style.color = 'white';
            headers.forEach(headers => {
                let th = document.createElement('th');
                th.textContent = headers;
                tr.appendChild(th);
            });
            table.appendChild(tr);

            timeline.forEach(item => {
                console.log(item);  // Log the current item
                let tr = document.createElement('tr');

                // For each item, create a new cell for each property and append it to the row
                tableNames.forEach(tableNames => {
                    let td = document.createElement('td');
                    if(tableNames === 'nationalflag'){
                        td.innerHTML = '<img src="' + item[tableNames].toLowerCase() + '" alt="Flag" style="width: auto; height: auto; padding: 2px;">';
                    } else
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
xhttp.open("GET", "./php/driverOverview.php", true);
xhttp.send();