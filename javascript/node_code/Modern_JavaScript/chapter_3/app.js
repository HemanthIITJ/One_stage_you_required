
function errorCallback(cb) {
    setTimeout(() => cb(new Error('fail')), 100);
  }
  errorCallback((err, data, data1,data2) => {
    if (err) 
      console.error('Callback Error:', err.message);
  });