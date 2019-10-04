const functions = require('firebase-functions');
const admin = require('firebase-admin');
admin.initializeApp(functions.config().firebase);
let db = admin.firestore();

exports.addMessage = functions.https.onRequest(async (req, res) => {
	const num = Number(req.query.num);
	const active = req.query.active;
	const alt = Number(req.query.alt);
	const lat = Number(req.query.lat);	//위도 =
	const lng = Number(req.query.lng);	//경도 ||
	const pos = new admin.firestore.GeoPoint(lat, lng);
	const rot = Number(req.query.rot);

	// Push the new message into the Realtime Database using the Firebase Admin SDK.
	const snapshot1 = await db.collection('drones')
		.doc('test_drone'+num)
		.set({
			active: active,
			alt: alt,
			pos: pos,
			rotate: rot
		});
	res.send(200,"OK: SUCCESS to #" + num);
});