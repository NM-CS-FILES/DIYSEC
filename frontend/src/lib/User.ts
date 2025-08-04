export class User {
	private username: string;
	private password: string;
	private token: string;
	private email: string;

	constructor(name: string, pswd: string, tkn: string, emailAddr: string) {
		this.username = name;
		this.password = pswd;
		this.token = tkn;
		this.email = emailAddr;
	}
	
	public getUsername() {return this.username;}
	public getPassword() {return this.password;}
	public getToken() {return this.token;}
	public getEmail() {return this.email;}

	public setUsername(name: string) {
		this.username = name;
	}
	public setPassword(pswd: string) {
		this.password = pswd;
	}
	public setToken(tkn: string) {
		this.token = tkn;
	}
	public setEmail(emailAddr: string) {
		this.email = emailAddr;
	}
}