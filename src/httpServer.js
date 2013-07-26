var http = require('http')

http.createServer(function(request, response) {
        var ip = request.connection.remoteAddress;
        var port = request.connection.port;
        console.log('Connection received from ' + ip + ' ' + port);
        response.writeHead(200, {'Content-Type': 'text'});
        response.write(ip + ' ' + port);
        response.end();
}).listen(10005);
