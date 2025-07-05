export class Session {

    static server: string | null = null;
    static authToken: string | null = null; 

    static login(username: string, password: string): boolean {
        if (Session.server === null) {
            return false;
        }

        fetch(Session.server, {
            method: "POST",
            body: JSON.stringify({ 
                username: username,
                password: password
            }),
            headers: {
                "Content-Type": "application/json"
            }
        })
        .then(resp => {
            if (resp.headers.has("Authorization")) {
                Session.authToken = resp.headers.get("Authorization");
            }
        });

        return Session.authToken !== null;
    }

}