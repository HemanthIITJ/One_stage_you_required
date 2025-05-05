function fetchDataPromise() {
  return new Promise(res => setTimeout(() => res('data1'), 100));
}
fetchDataPromise().then(data => fetchDataPromise().then(data2 => console.log('Promise:', data, data2)));
