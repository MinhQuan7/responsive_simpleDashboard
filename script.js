//Cập nhật thời gian
function updateClock() {
  const now = new Date();
  const options = {
    hour: "2-digit",
    minute: "2-digit",
    second: "2-digit",
    hour12: false,
    year: "numeric",
    month: "2-digit",
    day: "2-digit",
  };

  document.getElementById("clock").textContent = now.toLocaleString(
    "vi-VN",
    options
  );
}
// Cập nhật đồng hồ mỗi giây
updateClock();
setInterval(updateClock, 1000);

//____________E-Ra_______________________
// const eraWidget = new EraWidget();
// const currentId = "Current"; // ID chuỗi cho dòng điện
// const voltageId = "Voltage"; // ID chuỗi cho điện áp
// const pwId = "Power"; // ID số cho công suất tiêu thụ

// let configCurrent = null,
//   configVol = null,
//   configPower = null;

// eraWidget.init({
//   onConfiguration: (configuration) => {
//     // Lưu các cấu hình khi nhận được từ widget
//     configCurrent = configuration.realtime_configs[0]; // Lưu cấu hình dòng điện
//     configVol = configuration.realtime_configs[1]; // Lưu cấu hình điện áp
//     configPower = configuration.realtime_configs[2]; // Lưu cấu hình power
//   },

//   // Hàm lấy giá trị từ các ID và cập nhật giao diện
//   onValues: (values) => {  
//       const voltageVal = values[configVol.id].value;
//       const currentVal = values[configCurrent.id].value;
//       const powerVal = values[configPower.id].value;

//       currentId.textContent = currentVal;
//       voltageId.textContent = voltageVal
//       pwId.textContent = powerVal;

//   },
// });
