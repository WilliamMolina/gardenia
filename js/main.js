     let client = mqtt.connect('wss://iot.eclipse.org:443/ws');
      client.subscribe("gardenia/plant/humidity");
      client.subscribe("gardenia/plant/temperature");
      //client.subscribe("gardenia/plant/moisture");
      client.subscribe("gardenia/plant/watering");
      client.on("message", function (topic, payload) {
        let sensor = topic.split('/')[2];
        if(sensor == 'watering'){
            let label = document.getElementById('last_watering');
            let d = new Date(Number(payload.toString()));
            let datestring = ("0" + d.getDate()).slice(-2) + "-" + ("0"+(d.getMonth()+1)).slice(-2) + "-" +
            d.getFullYear() + " " + ("0" + d.getHours()).slice(-2) + ":" + ("0" + d.getMinutes()).slice(-2);
            label.innerText = datestring;
        }else{
            let label = document.getElementById(sensor);
            label.innerText = payload;
        }      
      });