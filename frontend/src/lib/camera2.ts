export class Camera {
	camID: string;
	lastFrame: string;

	constructor(id: number) {
		this.camID = `${id}`;
		this.lastFrame = "/placeholder.jpg"; // use a real URL if available
	}
}
