 //Cập nhật thời gian 
function updateClock() {
          const now = new Date();
          const options = {
              hour: '2-digit',
              minute: '2-digit',
              second: '2-digit',
              hour12: false,
              year: 'numeric',
              month: '2-digit',
              day: '2-digit'
          };
          
          document.getElementById('clock').textContent = 
              now.toLocaleString('vi-VN', options);
      }
      // Cập nhật đồng hồ mỗi giây
      updateClock();
      setInterval(updateClock, 1000);
      
      
//____________E-Ra_______________________
  const eraWidget = new EraWidget();

  // Khai báo các ID cho humid, temp, và power
  const currentId = "Current"; // ID chuỗi cho dòng điện
  const voltageId = "Voltage"; // ID chuỗi cho điện áp 
  const pwId = "Power"; // ID số cho công suất tiêu thụ

  let configCurent = null,
    configVol = null,
    configPower = null;

  eraWidget.init({
    onConfiguration: (configuration) => {
      // Lưu các cấu hình khi nhận được từ widget
      configCurent = configuration.realtime_configs[0]; // Lưu cấu hình dòng điện
      configVol = configuration.realtime_configs[1]; // Lưu cấu hình điện áp
      configPower = configuration.realtime_configs[2]; // Lưu cấu hình power
      actions = configuration.actions; // Lưu các hành động điều khiển
    },

    // Hàm lấy giá trị từ các ID và cập nhật giao diện
    onValues: (values) => {
      if (configVol && values[configVol.id]) {
        const voltageVal = values[configVol.id].value;
        document.getElementById("voltageId").textContent = voltageVal; // Cập nhật giá trị độ ẩm
      }

      if (configCurent && values[configCurent.id]) {
        const currentVal = values[configCurent.id].value;
        document.getElementById("current-id").textContent = currentVal; // Cập nhật giá trị nhiệt độ
      }

      if (configPower && values[configPower.id]) {
        const powerVal = values[configPower.id].value;
        document.getElementById("power").textContent = powerVal; // Cập nhật giá trị công suất tiêu thụ
      } else {
        console.error("Không tìm thấy cấu hình hoặc giá trị cho Power.");
      }
    },
  });
  // Kích hoạt các hành động dựa trên trạng thái của công tắc
  turnOn.addEventListener("click", () => {
    eraWidget.triggerAction(actions[0]?.action, null); // Kích hoạt hành động "Bật đèn"
  });
  turnOff.addEventListener("click", () => {
    eraWidget.triggerAction(actions[1]?.action, null); // Kích hoạt hành động "Tắt đèn"
  });
