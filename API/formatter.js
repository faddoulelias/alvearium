function decodeUplink(input) {
	tempByte = new Uint8Array(input.bytes.slice(0, 4)).buffer;
	humiByte = new Uint8Array(input.bytes.slice(4, 8)).buffer;

	temp = new DataView(tempByte).getFloat32(0, true);
	humi = new DataView(humiByte).getFloat32(0, true);

	return {
		data: {
			//tempByte:tempByte,
			//humiByte:humiByte,
			temperature: temp,
			humidity: humi,
		},
		warnings: [],
		errors: [],
	};
}
