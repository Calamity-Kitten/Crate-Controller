var varBrightnessInput = document.getElementById("brightnessInput");
var hostName = "http://192.168.5.246";

function httpGet(theUrl)
{
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", theUrl, false ); // false for synchronous request
	xmlHttp.send( null );
	return xmlHttp.responseText;
}

function getBrightnessValue() {
	var request = httpGet("brightness");
	brightnessOutput.value = request;
	varBrightnessInput.value = request;
	return request;
}

function setBrightnessValue() {
	var newBrightness = varBrightnessInput.value;
	var request = httpGet("brightness/" + newBrightness);
	brightnessOutput.value = request;
	varBrightnessInput.value = request;
	return request;
}

document.addEventListener("DOMContentLoaded", getBrightnessValue);

varBrightnessInput
	.addEventListener('input', setBrightnessValue);