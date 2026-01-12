let queue = [];

function render() {
    const display = document.getElementById('queue-display');
    display.innerHTML = ''; // Clear current view
    queue.forEach(person => {
        const div = document.createElement('div');
        div.className = 'customer-box';
        div.innerText = person;
        display.appendChild(div);
    });
}

function enqueue() {
    const name = document.getElementById('nameInput').value;
    if(name) {
        queue.push(name); // Add to end
        render();
    }
}

function dequeue() {
    queue.shift(); // Remove from front
    render();
}