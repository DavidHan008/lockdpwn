시스템최신기술 과제 제출
모든 코드는 systemNewTechnology 폴더 안에 있습니다

Mission #4, #5를 하나의 60초 데모 비디오로 구성.  한 화면에 소스코드 2가지 각각 (온도를 ThingSpeak로도 쏘고, 이어서 여러분 서버로도 쏘는 것) (웹서버인데 화일에도 저장하고, 데이타베이스에도 저장) 화면에 ssh를 여러개 띄워놓고 한번에 비디오 찍도록 함.

- Youtube URL (Mission 4,5) :    [https://youtu.be/9D-_BwH0Was]
- thingspeak URL :             [https://thingspeak.com/channels/248481]

# Mission 4 :
 node.js 설치 및 간단웹서버 구축, http로 온도 데이타 받아서 화일에 포맷팅하여 저장하는 프로그램 작성, github에 올림
# Mission 5 :
 Mission 4의 연장으로, mysql을 설치하고 온도 데이타를 database에 저장시킴, 프로그램을 github에 올림.

파이썬 코드입니다
```python
import os
import time
import urllib
import json
import httplib
import requests

sleep = 5
key = 'PC45B10F37HRMZ0P'

temp_sensor='/sys/bus/w1/devices/28-0416935fd1ff/w1_slave'

os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')


def temp_raw():
    f = open(temp_sensor,'r')
    lines = f.readlines()
    f.close()
    return lines


def read_temp():
    lines = temp_raw()
    while lines[0].strip()[-3:] != 'YES':
        time.sleep(0.2)
        lines = temp_raw()

    temp_output = lines[1].find('t=')

    if temp_output != -1:
        temp_string = lines[1].strip()[temp_output+2:]
        temp_c = float(temp_string) / 1000.0
        temp_f = temp_c * 9.0/5.0 + 32.0
        return temp_c, temp_f


def thermometer():
    while True:
        temp = read_temp()[0]
        headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
        params = urllib.urlencode({'field1': temp, 'key':key })
        conn = httplib.HTTPConnection("api.thingspeak.com:80")

        try:
            print(" ")
            print "[+] ThingSpeak"
            conn.request("POST", "/update", params, headers)
            response = conn.getresponse()
            print temp
            print response.status, response.reason
            data = response.read()
            conn.close()

            print "[+] Node.js"
            r = requests.get('http://192.168.137.74:3000/logone', params={'temp':temp})
            print r.status_code

        except:
            print "connection failed"
        break



if __name__ == "__main__":
    while True:
        thermometer()
        time.sleep(sleep)

```

Node.js 코드입니다
```javascript
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
		console.log("[+]SQL injection is done!");
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
```


