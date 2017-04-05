// 
// nodejs ==> 시스템최신기술, nodejs로 ds18b20의 센서데이터를 읽어오는 코드
//

var express = require('express');
var app = express();

bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({extended: false}));

var fs = require("fs");
var df = require('dataformat');

mysql = require('mysql');
var connection = mysql.createConnection({
	host:'localhost',
	user:'sensor',
	password:'qwer1234',
	database:'data'
})
connection.connect();


function insert_sensor(user, type, value, user2, serial, ip)
{
	obj = {};
	obj.user = user;
	obj.type = type;
	obj.value = value;
	obj.user2 = user2;
	obj.serial = serial;
	obj.ip = ip
	obj.date = df(new Date(), "yyyy-mm-dd HH:MM:ss");

	var d = JSON.stringify(obj);
	ret = " "+ type + user2 +"="+ value;

	//console.log("RET "+ ret);
	//
	fs.appendFile("Data.txt", d+'\n', function(err) {
		if(err) console.log("File Write Err: %j", r);
	});
	return(ret);
}


function do_get_post(cmd, r, req, res)
{
	console.log(cmd +" %j", r);
	ret_msg = "{serial:"+ r.serial +",user:"+ r.user;

	if (r.format == '2') {
		//console.log("got format 2");
		var items = r.items.split(',');

		for (var i=0; i< items.length; i++) {
			if (items[i].length < 3) continue;
			var v = items[i].split('-');
			ret_msg += insert_sensor(r.user, v[1], v[2], v[0], r.serial, req.connection.remoteAddress);
		}
	}

	ret_msg += "}";
	res.writeHead(200, {'Content-Type': 'text/plain'});
	res.end('X-ACK:' + ret_msg);
}


app.get("/data", function(req, res){
	console.log("params=" + req.query);

	var qstr = 'select * from sensors where time > date_sub(now(), INTERVAL 1 DAY)';

	connection.query(qstr, function(err, rows, cols){
		if(err){
			throw err;
			res.send('query error: ' +qstr);
			return;
		}

		console.log("Got " + rows.length +" records");
		var html = "<!doctype html><html><body>";
		html += "<H1> Sensor Data for Last 24 Hours </H1>";
		html += "<table border=1 cellpadding=3 cellspacing=0>";
		html += "<tr><td>Seq#<td>Time Stamp<td>Temperature";

		for(var i =0; i < rows.length ; i++)
		{
			html += "<tr><td>"+ JSON.stringify(rows[i]['seq'])+"<td>"+ JSON.stringify(rows[i]['time'])+"<td>"+ JSON.stringify(rows[i]['value']);
		}
		html += "</table>";
		html += "</body></html>";
		res.send(html);
	});
});



app.get('/logone', function(req, res){
	var i = 0;
	i++;

	r = {};
	r.seq = i;
	r.type = 'T';
	r.device = '102';
	r.unit = '0';
	r.ip = req.ip;
	r.value = req.query.temp;

	var query = connection.query('insert into sensors set ?', r, function(err, rows,cols){
		if(err)
		{
			throw err;
		}
		console.log("sql injection is done");
	});
	
	var date = new Date();
	fs.appendFile("log.txt",JSON.stringify(req.query) +", "+req.ip+", "+ date +"\n" ,function(err){
	if(err){
			return console.log(err);
		}
	})
	r = req.query;
	do_get_post("GET", r, req, res);
});




app.post('/logone', function(req, res){
	r = {};
	r.seq = 1;
	r.type = 'T';
	r.device = '102';
	r.unit = '0';
	r.ip = req.ip;
	r.value = req.query.temp;

	var query = connection.query('insert into sensors set ?', r, function(err, rows,cols){
		if(err)
		{
			throw err;
		}
		console.log("done");
	});

	var date = new Date();

	fs.appendFile("log.txt",JSON.stringify(req.query) +", "+req.ip+", "+ date +"\n" ,function(err){
		if(err){
			return console.log(err);
		}
	})

	r = req.body;
	do_get_post("POST", r, req, res);
});


var server = app.listen(3000, function(){
	var host = server.address().address
	var port = server.address().port
	console.log('listening at http://%s:%s',host,port)
});
		
