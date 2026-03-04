var varBrightnessInput = document.getElementById("brightnessInput");
var varMinimumTimeInput = document.getElementById("minimumTimeInput");
var varMaximumTimeInput = document.getElementById("maximumTimeInput");
var varStaticTimeInput = document.getElementById("staticTimeInput");
var varGameModeInput = document.getElementById("gameModeInput");
// var varSubmitButton = document.getElementById("submit");

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
window.addEventListener('load', onLoad);
submit.addEventListener('click', submitSettings);

varBrightnessInput.addEventListener('input', function() {
	ping();
});
varMinimumTimeInput.addEventListener('input', function() {
	ping();
	if (minimumTimeInput.valueAsNumber > maximumTimeInput.valueAsNumber) {
		maximumTimeInput.value = minimumTimeInput.value;
	}
});
varMaximumTimeInput.addEventListener('input', function() {
	ping();
	if (maximumTimeInput.valueAsNumber < minimumTimeInput.valueAsNumber) {
		minimumTimeInput.value = maximumTimeInput.value;
	}
});
varStaticTimeInput.addEventListener('input', function() {
	ping();
});

function initWebSocket() {
	console.log('Trying to open a WebSocket connection...');
	websocket = new WebSocket(gateway);
	websocket.onopen    = onOpen;
	websocket.onclose   = onClose;
	websocket.onmessage = onMessage; // <-- add this line
}

function onOpen(event) {
	console.log('Connection opened');
}

function onClose(event) {
	console.log('Connection closed');
	setTimeout(initWebSocket, 2000);
}

function onLoad(event) {
	initWebSocket();
}

// TODO: Replace output field with reset button,
// change setting class based on if it matches server setting
function onMessage(event) {
	let data = JSON.parse(event.data);
	console.log(data);

	if (brightnessInput.value == data.Brightness)
		brightnessInput.parentElement.classList.remove("diff");
	else brightnessInput.parentElement.classList.add("diff");

	if (maximumTimeInput.value == data.MaximumTime)
		maximumTimeInput.parentElement.classList.remove("diff");
	else maximumTimeInput.parentElement.classList.add("diff");

	if (minimumTimeInput.value == data.MinimumTime)
		minimumTimeInput.parentElement.classList.remove("diff");
	else minimumTimeInput.parentElement.classList.add("diff");

	if (staticTimeInput.value == data.StaticTime)
		staticTimeInput.parentElement.classList.remove("diff");
	else staticTimeInput.parentElement.classList.add("diff");
}

// TODO: this shouldn't change slider values, but should change output value and add visual indicator
function submitSettings() {
	console.log("Submit!");
	websocket.send(
		JSON.stringify(
			{
				'Brightness' : brightnessInput.value,
				'MaximumTime' : maximumTimeInput.value,
				'MinimumTime' : minimumTimeInput.value,
				'StaticTime' : staticTimeInput.value,
				'GameMode' : gameModeInput.value
			}
		)
	);
}

function ping() {
	websocket.send(JSON.stringify({}));
}