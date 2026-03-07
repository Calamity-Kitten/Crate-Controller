const ctx = document.getElementById('myChart');
var jsChart;

function getGameLog() {
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open("GET", "/GameLog", false);
	xmlHttp.send(null);
	return xmlHttp.responseText.split("\n");
}

function getHistogramData() {
	var input = getGameLog();
	var maxTime = Math.max.apply(null, input);
	var maxTier = Math.trunc(maxTime / (chartScale.value));

	var bars = new Array(maxTier + 1).fill(0);
	input.forEach((val) => {
		bars[Math.trunc(val / (chartScale.value))] += 1;
	});

	console.log("maxTier: " + maxTier);
	console.log(input);
	console.log(bars);

	return bars;
}

function drawHistogram() {
	var data = getHistogramData();

	var labels = Array(data.length);
	for (let i = 0; i < data.length; i++) {
		labels[i] = i;
	}

	jsChart = new Chart(ctx, {
		type: 'bar',
		data: {
			labels: labels,
			datasets: [{
				label: 'Reaction Time',
				data: data,
				borderWidth: 1
			}]
		},
		options: {
			scales: {
				y: {
					beginAtZero: true,
					title: 'Frequency'
				},
				x: {
					title: 'Time [Minutes]'
				}
			}
		}
	});
}

function updateHistogram() {
	var data = getHistogramData();

	var labels = Array(data.length);
	for (let i = 0; i < data.length; i++) {
		labels[i] = i;
	}

	jsChart.data.labels = labels;
	jsChart.data.datasets[0].data = data;
	jsChart.update();
}

chartScale.addEventListener('input', updateHistogram);
refreshChart.addEventListener('click', updateHistogram);
drawHistogram();