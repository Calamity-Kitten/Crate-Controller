var varBrightnessInput = document.getElementById("brightnessInput");
var varMinimumTimeInput = document.getElementById("minimumTimeInput");
var varMaximumTimeInput = document.getElementById("maximumTimeInput");
var varStaticTimeInput = document.getElementById("staticTimeInput");
var varGameModeInput = document.getElementById("gameModeInput");

var min2ms = 60 * 1000;

function httpGet(theUrl) {
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open("GET", theUrl, false); // false for synchronous request
	xmlHttp.send(null);
	return xmlHttp.responseText;
}

function initSettings() {
	getBrightnessValue();
	getMinimumTimeValue();
	getMaximumTimeValue();
	getStaticTimeValue();
	getGameModeValue();

	var settings = document.querySelectorAll('.setting')//.style.display = 'block';
	for(var i = 0; i < settings.length; i++) {
		settings[i].style.display = 'block';
	}
}

function submitSettings() {
	setBrightnessValue();
	setMaximumTimeValue();
	setMinimumTimeValue();
	setStaticTimeValue();
	setGameModeValue();
}

function getSelectValue(URI_name, inputField) {
	var request = httpGet(URI_name);
	console.log("Get " + URI_name + ": " + request);
	inputField.value = request;
	return request;
}

function setSelectValue(URI_name, inputField) {
	var newVal = inputField.value;
	var request = httpGet(URI_name + "/" + newVal);
	console.log("Set " + URI_name + ": " + inputField.value + " Return: " + request);
	inputField.value = request;
	return request;
}

function SelectValueChanged(URI_name, inputField) {
	var request = httpGet(URI_name) / saveFactor;
	console.log("Get " + URI_name + ": " + request);
	//TODO: add CSS
	if (request != inputField.value) {
		inputField.classList.add("diff");
	}
	return request;
}

function getRangeValue(URI_name, inputField, outputField, saveFactor=1) {
	var request = httpGet(URI_name) / saveFactor;
	console.log("Get " + URI_name + ": " + request);
	inputField.value = request;
	outputField.value = request;
	return request;
}

function setRangeValue(URI_name, inputField, outputField, saveFactor=1) {
	var newVal = inputField.value * saveFactor;
	var request = httpGet(URI_name + "/" + newVal) / saveFactor;
	console.log("Set " + URI_name + ": " + inputField.value + " Return: " + request);
	inputField.value = request;
	outputField.value = request;
	return request;
}

function RangeValueChanged(URI_name, inputField, outputField, saveFactor=1) {
	var request = httpGet(URI_name) / saveFactor;
	console.log("Get " + URI_name + ": " + request);
	outputField.value = inputField.value;
	//TODO: add CSS
	if (request != inputField.value) {
		inputField.classList.add("diff");
		outputField.classList.add("diff");
	}
	return request;
}

function getBrightnessValue() {
	getRangeValue("Brightness", varBrightnessInput, brightnessOutput);
}

function setBrightnessValue() {
	RangeValueChanged("Brightness", varBrightnessInput, brightnessOutput);
}

function getMaximumTimeValue() {
	getRangeValue("MaximumTime", varMaximumTimeInput, maximumTimeOutput, min2ms);
}

function setMaximumTimeValue() {
	RangeValueChanged("MaximumTime", varMaximumTimeInput, maximumTimeOutput, min2ms)
}

function getMinimumTimeValue() {
	getRangeValue("MinimumTime", varMinimumTimeInput, minimumTimeOutput, min2ms);
}

function setMinimumTimeValue() {
	RangeValueChanged("MinimumTime", varMinimumTimeInput, minimumTimeOutput, min2ms);
}

function getStaticTimeValue() {
	getRangeValue("StaticTime", varStaticTimeInput, staticTimeOutput, min2ms);
}

function setStaticTimeValue() {
	RangeValueChanged("StaticTime", varStaticTimeInput, staticTimeOutput, min2ms);
}

function getGameModeValue() {
	getSelectValue("GameMode", varGameModeInput);
}

function setGameModeValue() {
	setSelectValue("GameMode", varGameModeInput);
}

document.addEventListener("DOMContentLoaded", initSettings);

varBrightnessInput.addEventListener('input', setBrightnessValue);
varMinimumTimeInput.addEventListener('input', setMinimumTimeValue);
varMaximumTimeInput.addEventListener('input', setMaximumTimeValue);
varStaticTimeInput.addEventListener('input', setStaticTimeValue);
varGameModeInput.addEventListener('input', setGameModeValue);
