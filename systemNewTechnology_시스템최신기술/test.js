mysql = require('mysql');

var connection = mysql.createConnection({
	host: 'localhost',
	user: 'sensor',
	password: 'qwer1234',
	database: 'data'
})
connection.connect();

r = {};
r.seq = 1;
r.type= 'T';
r.device='102';
r.unit='0';
r.ip="192.168.0.2";
r.value=10.9;

var query = connection.query('insert into sensors set ?', r, function(err,rows,cols){
	if(err) throw err;
	console.log("done");
	process.exit();
});

app.get('/graph', function(req, res){
	console.log('got app.get(graph)');
	var html = fs.readFile('./graph1.html', function (err, html) {
		html = " "+ html
		console.log('read file');

		var qstr = 'select * from sensors ';
		connection.query(qstr, function(err, rows, cols) {
			if (err) throw err;

			var data = "";
			var comma = ""
			for (var i=0; i< rows.length; i++) {
				r = rows[i];
				data += comma + "[new Date(2017,04-1,"+ r.id +",00,38),"+ r.value +"]";
				comma = ",";
			}
			var header = "data.addColumn('date', 'Date/Time');"
			header += "data.addColumn('number', 'Temp');"
			html = html.replace("<%HEADER%>", header);
			html = html.replace("<%DATA%>", data);

			res.writeHeader(200, {"Content-Type": "text/html"});
			res.write(html);
			res.end();
		});
	});
})



app.listen(3000, function(){
	console.log("app listening on port 3000!");
})

