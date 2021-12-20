// self executing function here
(function() {
  var svg = document.getElementById('mysvg');
  var v = document.createElementNS("http://www.w3.org/2000/svg", 'rect');
  v.setAttribute('x', '30');
  v.setAttribute('y', '50');
  v.setAttribute('width', '30');
  v.setAttribute('height', '60');
  v.setAttribute('fill', '#888');
  svg.appendChild(v);
})();


function newtree() {
  var svg = document.getElementById('mysvg');
  while (svg.firstChild) svg.removeChild(svg.firstChild);
  var textarea = document.getElementById('inputbox');
  var p = textarea.value;
  var a = p.split(',').map((x) => x.trim());
  console.log(a);
}

function gensequence() {
  var a = Array.from({length: 40}, () => Math.floor(Math.random() * 40));
  var textarea = document.getElementById('inputbox');
  textarea.value = a.join(',');
}