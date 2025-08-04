export class Recording {
	//private recording: number[] = [];  // Not sure how to implement the recordings yet
	private recording: string = "./placeholder.mp4"
	private cameraID: string;  // stored as a string instead of number so that it can be in the UI (at least that's how it worked in the playground)
	private date: string;
	private duration: number;
	private time: string;

	constructor(camID: number, recDate: string, recDuration: number, recTime: string) {  //NEEDS EDITING FOR INTEGRATION
		this.cameraID = `${camID}`;
		this.date = recDate;
		this.duration = recDuration;
		this.time = recTime;
	}
/**/
	public getRecording() {return this.recording;}
	public getCameraID() {return this.cameraID;}
	public getDate() {return this.date;}
	public getDuration() {return this.duration;}
	public getTime() {return this.time;}

	public setRecording(savedRec: string) {
        this.recording = savedRec;
    }
    /*public setRecording(savedRec: number[]) {
		//recording: string
		//this.recording = recording
		for (let i = 0; i < savedRec.length; i++) {
			this.recording[i] = savedRec[i];
		}
	}*/
	public setCameraID(camID: number) {
		//this.cameraID = `${camID}`;
	}
	public setDate(recDate: string) {
		this.date = recDate;
	}
	public setDuration(recDuration: number){
		this.duration = recDuration;
	}
	public setTime(recTime: string) {
		this.time = recTime;
	}
}