export class Camera {
  
    id: number;
    ws: WebSocket | null;

    constructor(id: number) {
        this.id = id;
        this.ws = null;
    }

};