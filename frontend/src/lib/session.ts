interface LoginResponse {
    Authorization: string;
};

interface CameraResponse {
    camera_ids: Array<Number>;
};

export class Session {
    private static server: string = "http://localhost:8888";
    private static apiUrl = Session.server + "/api";
    private static authToken: string = ""; 
    private static cameras: Array<Number> = [];

    static async login(username: string, password: string): Promise<void> {
        if (Session.server === null) {
            return Promise.resolve();
        }

        let response = await fetch(Session.apiUrl + "/login", {
            method: "POST",
            body: JSON.stringify({ 
                username: username,
                password: password
            }),
            headers: {
                "Content-Type": "application/json"
            }
        })

        if (!response.ok)
            return;

        const authData: LoginResponse = await response.json();

        Session.authToken = authData.Authorization;
    }

    static async register(username: string, password: string): Promise<void> {
        if (Session.server === null) {
            return Promise.resolve();
        }

        let response = await fetch(Session.apiUrl + "/register", {
            method: "POST",
            body: JSON.stringify({ 
                username: username,
                password: password
            }),
            headers: {
                "Content-Type": "application/json"
            }
        })

        if (!response.ok)
            return;

        const authData: LoginResponse = await response.json();

        Session.authToken = authData.Authorization;
    }

    static async fetchCameras(): Promise<void> {
        if (Session.server === null) {
            return Promise.resolve();
        }

        let response = await fetch(Session.apiUrl + "/cameras", {
            headers: {
                "Authorization": Session.authToken
            }
        })

        if (!response.ok)
            return;

        const cameraData: CameraResponse = await response.json();

        Session.cameras = cameraData.camera_ids;
    }

    static getCameras(): Array<Number> {
        return Session.cameras;
    }

    static isAuthenticated(): boolean {
        return Session.authToken.length !== 0;
    }

}