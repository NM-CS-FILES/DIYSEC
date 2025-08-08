export class Session {

    private static server: string = "http://localhost:8888";
    private static apiUrl = Session.server + "/api";
    private static authToken: string | null = null; 

    static login(username: string, password: string): Promise<void> {
        if (Session.server === null) {
            return Promise.resolve();
        }

        let fetchPromise = fetch(this.apiUrl + "/login", {
            mode: "no-cors",
            method: "POST",
            body: JSON.stringify({ 
                username: username,
                password: password
            }),
            headers: {
                "Content-Type": "application/json"
            }
        });

        let promise = fetchPromise.then(resp => {

            if (resp.headers.has("Authorization")) {
                Session.authToken = resp.headers.get("Authorization");
            }
        });

        return promise;
    }

    static isAuthenticated(): boolean {
            console.log("ISAUTHED");
        return Session.authToken !== null;
    }

}