var varBrightnessInput = document.getElementById("brightnessInput");
var varMinimumTimeInput = document.getElementById("minimumTimeInput");
var varMaximumTimeInput = document.getElementById("maximumTimeInput");
var varStaticTimeInput = document.getElementById("staticTimeInput");
var varGameModeInput = document.getElementById("gameModeInput");
var varSubmitButton = document.getElementById("submit");

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
	console.log("Submit!");
	setBrightnessValue();
	setMaximumTimeValue();
	setMinimumTimeValue();
	setStaticTimeValue();
	setGameModeValue();
	httpGet("SaveSettings");
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
	inputField.classList.remove("diff");
	return request;
}

function SelectValueChanged(URI_name, inputField) {
	var request = httpGet(URI_name);
	console.log("Get " + URI_name + ": " + request);
	//TODO: add CSS
	if (request != inputField.value) {
		inputField.classList.add("diff");
	} else {
		inputField.classList.remove("diff");
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
	inputField.classList.remove("diff");
	outputField.classList.remove("diff");
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
	} else {
		inputField.classList.remove("diff");
		outputField.classList.remove("diff");
	}
	return request;
}

function getBrightnessValue() {
	getRangeValue("Brightness", varBrightnessInput, brightnessOutput);
}

function setBrightnessValue() {
	setRangeValue("Brightness", varBrightnessInput, brightnessOutput);
}

function changeBrightnessValue() {
	RangeValueChanged("Brightness", varBrightnessInput, brightnessOutput);
}

function getMaximumTimeValue() {
	getRangeValue("MaximumTime", varMaximumTimeInput, maximumTimeOutput, min2ms);
}

function setMaximumTimeValue() {
	setRangeValue("MaximumTime", varMaximumTimeInput, maximumTimeOutput, min2ms)
}

function changeMaximumTimeValue() {
	RangeValueChanged("MaximumTime", varMaximumTimeInput, maximumTimeOutput, min2ms)
}

function getMinimumTimeValue() {
	getRangeValue("MinimumTime", varMinimumTimeInput, minimumTimeOutput, min2ms);
}

function setMinimumTimeValue() {
	setRangeValue("MinimumTime", varMinimumTimeInput, minimumTimeOutput, min2ms);
}

function changeMinimumTimeValue() {
	RangeValueChanged("MinimumTime", varMinimumTimeInput, minimumTimeOutput, min2ms);
}

function getStaticTimeValue() {
	getRangeValue("StaticTime", varStaticTimeInput, staticTimeOutput, min2ms);
}

function setStaticTimeValue() {
	setRangeValue("StaticTime", varStaticTimeInput, staticTimeOutput, min2ms);
}

function changeStaticTimeValue() {
	RangeValueChanged("StaticTime", varStaticTimeInput, staticTimeOutput, min2ms);
}

function getGameModeValue() {
	getSelectValue("GameMode", varGameModeInput);
}

function setGameModeValue() {
	setSelectValue("GameMode", varGameModeInput);
}

function changeGameModeValue() {
	SelectValueChanged("GameMode", varGameModeInput);
}

document.addEventListener("DOMContentLoaded", initSettings);

varBrightnessInput.addEventListener('input', changeBrightnessValue);
varMinimumTimeInput.addEventListener('input', changeMinimumTimeValue);
varMaximumTimeInput.addEventListener('input', changeMaximumTimeValue);
varStaticTimeInput.addEventListener('input', changeStaticTimeValue);
varGameModeInput.addEventListener('input', changeGameModeValue);
varSubmitButton.addEventListener('click', submitSettings);