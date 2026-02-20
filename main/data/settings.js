var varBrightnessInput = document.getElementById("brightnessInput");
var varMinimumTimeInput = document.getElementById("minimumTimeInput");
var varMaximumTimeInput = document.getElementById("maximumTimeInput");
var hostName = "http://192.168.5.246";

function httpGet(theUrl)
{
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", theUrl, false ); // false for synchronous request
	xmlHttp.send( null );
	return xmlHttp.responseText;
}

function initSettings() {
	getBrightnessValue();
	getMinimumTimeValue();
}

function getBrightnessValue() {
	console.log("Get brightness");
	var request = httpGet("Brightness");
	brightnessOutput.value = request;
	varBrightnessInput.value = request;
	return request;
}

function setBrightnessValue() {
	var newBrightness = varBrightnessInput.value;
	var request = httpGet("Brightness/" + newBrightness);
	console.log("Set brightness. Old: " + varBrightnessInput.value + " New: " + newBrightness + " Return: " + request);
	brightnessOutput.value = request;
	varBrightnessInput.value = request;
	return request;
}

function getMaximumTimeValue() {
	var request = httpGet("MaximumTime") / (60 * 1000);
	console.log("Get Maximum Time: " + request);
	maximumTimeOutput.value = request;
	varMaximumTimeInput.value = request;
	return request;
}

function setMaximumTimeValue() {
	var newMaximumTime = varMaximumTimeInput.value * 60 * 1000;
	var request = httpGet("MaximumTime/" + newMaximumTime) / (60 * 1000);
	console.log("Set Maximum Time. Old: " + varMaximumTimeInput.value + " New: " + newMaximumTime + "(" + varMaximumTimeInput.value + ") Return: " + request);
	maximumTimeOutput.value = request;
	varMaximumTimeInput.value = request;
	return request;
}

function getMinimumTimeValue() {
	var request = httpGet("MinimumTime") / (60 * 1000);
	console.log("Get Minimum Time: " + request);
	minimumTimeOutput.value = request;
	varMinimumTimeInput.value = request;
	return request;
}

function setMinimumTimeValue() {
	var newMinimumTime = varMinimumTimeInput.value * 60 * 1000;
	var request = httpGet("MinimumTime/" + newMinimumTime) / (60 * 1000);
	console.log("Set Minimum Time. Old: " + varMinimumTimeInput.value + " New: " + newMinimumTime + "(" + varMinimumTimeInput.value + ") Return: " + request);
	minimumTimeOutput.value = request;
	varMinimumTimeInput.value = request;
	return request;
}

document.addEventListener("DOMContentLoaded", initSettings);

varBrightnessInput.addEventListener('input', setBrightnessValue);
varMinimumTimeInput.addEventListener('input', setMinimumTimeValue);
varMaximumTimeInput.addEventListener('input', setMaximumTimeValue);
