var http = require('http')
var url = require('url')
var exec = require("child_process").exec


function start(route, handle) {

	function onRequest(request, response) {
                var postData = "";
                var pathname = url.parse(request.url).pathname;

                console.log("Request for " + pathname + " received.");
                route(handle, pathname, response, request);
        }
	http.createServer(function(request, response) {
        	var ip = request.connection.remoteAddress;
        	var port = request.connection.port;
        	console.log('Message received from ' + ip + ' ' + port);
        	
		response.writeHead(200, {'Content-Type': 'text'});
        	response.write(ip + ' ' + port);
        	response.end();
	}).listen(10005);


