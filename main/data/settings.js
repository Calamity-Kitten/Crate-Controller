var varBrightnessInput = document.getElementById("brightnessInput");
var varMinimumTimeInput = document.getElementById("minimumTimeInput");
var varMaximumTimeInput = document.getElementById("maximumTimeInput");
var varStaticTimeInput = document.getElementById("staticTimeInput");

var min2ms = 60 * 1000;

function httpGet(theUrl)
{
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

	var settings = document.querySelectorAll('.setting')//.style.display = 'block';
	for(var i = 0; i < settings.length; i++) {
		settings[i].style.display = 'block';
	}
}

function getFieldValue(URI_name, inputField, outputField, saveFactor=1) {
	var request = httpGet(URI_name) / saveFactor;
	console.log("Get " + URI_name + ": " + request);
	inputField.value = request;
	outputField.value = request;
	return request;
}

function setFieldValue(URI_name, inputField, outputField, saveFactor=1) {
	var newVal = inputField.value * saveFactor;
	var request = httpGet(URI_name + "/" + newVal) / saveFactor;
	console.log("Set " + URI_name + ": " + inputField.value + " Return: " + request);
	inputField.value = request;
	outputField.value = request;
	return request;
}

function getBrightnessValue() {
	getFieldValue("Brightness", varBrightnessInput, brightnessOutput);
}

function setBrightnessValue() {
	setFieldValue("Brightness", varBrightnessInput, brightnessOutput);
}

function getMaximumTimeValue() {
	getFieldValue("MaximumTime", varMaximumTimeInput, maximumTimeOutput, min2ms);
}

function setMaximumTimeValue() {
	setFieldValue("MaximumTime", varMaximumTimeInput, maximumTimeOutput, min2ms)
}

function getMinimumTimeValue() {
	getFieldValue("MinimumTime", varMinimumTimeInput, minimumTimeOutput, min2ms);
}

function setMinimumTimeValue() {
	setFieldValue("MinimumTime", varMinimumTimeInput, minimumTimeOutput, min2ms);
}

function getStaticTimeValue() {
	getFieldValue("StaticTime", varStaticTimeInput, staticTimeOutput, min2ms);
}

function setStaticTimeValue() {
	setFieldValue("StaticTime", varStaticTimeInput, staticTimeOutput, min2ms);
}

document.addEventListener("DOMContentLoaded", initSettings);

varBrightnessInput.addEventListener('input', setBrightnessValue);
varMinimumTimeInput.addEventListener('input', setMinimumTimeValue);
varMaximumTimeInput.addEventListener('input', setMaximumTimeValue);
varStaticTimeInput.addEventListener('input', setStaticTimeValue);
