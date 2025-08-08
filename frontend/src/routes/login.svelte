<script lang="ts">
    import { onMount } from "svelte";
    import { goto } from "$app/navigation";
	
	let _username = $state('');
	let _pswd = $state('');
	let _confirm_pswd = $state('')
	let _email = $state('')
	let _login = $state(true);
	let _token = $state('');
	let _approved = $state(true);

	function createProfile() {
		let _valid_username = false;
		let _valid_password = false;
		let _valid_email = false;
		if (_username.length < 6 || _username.length > 12) {
			alert("Username must be between 6 and 12 charaters.")
		}
		else { _valid_username = true; }
		if (_pswd != _confirm_pswd) {  // If Password confirmation does not match
			alert("Password and confirmed password do not match.")
		}
		else { _valid_password = true; }
		if (_email == '') {
			alert("Email cannot be left blank.")
		}
		else if (!_email.includes("@") || !_email.includes(".com") || !_email.includes(".net") 
		|| !_email.includes(".org") || !_email.includes(".edu") || !_email.includes(".gov")) {
			alert("Must enter a valid email address.")
		}
		else { _valid_email = true; }
		if (_valid_username == true && _valid_password == true && _valid_email == true) {
			sendNewProfile();
		}
	}
	async function signIn() {
		const res = await fetch("https://localhost:8888/api/login",  {  // CHECK THAT URL IS CORRECT!!
			method: "POST",
			headers: {"Content-Type": "application/json"},  // Keep?
			body: JSON.stringify({username: _username, password: _pswd})
		});
		if (res.ok) {  // Ok status from server
			const data = await res.json();
			if (data.approved == true) {  // Checks if login was approved by server
				_email = data.email;
				_token = data.token;  // = data.Authorization??????
				storeUser();
				goto("./dashboard");
			}
			else {
				_username = ''; _pswd = '';
				_approved = false;
			}
		}
		else {
			alert("Status Error: " + `${res.status}`);
		}
	}
	async function sendNewProfile() {
		// FILL IN.... (POST method for sending account to server {maybe add conditions})
		const res = await fetch("https://localhost:8888/api/...", {  // UPDATE API URL!!
			method: "POST",
			headers: {"Content-Type": "application/json"},
			body: JSON.stringify({username: _username, password: _pswd, email: _email})
		})
		if (res.ok) {
			const data = await res.json();
			if (data.approved == true) {
				_username = '';	_pswd = '';	_confirm_pswd = '';
				_login = true;
			}
			else {  // Need to add methods to stop just anyone from creating a profile!

			}
		}
		else {
			alert("Account not created. Status Error: " + `${res.status}`);
		}
		
	}
	function storeUser() {
		sessionStorage.setItem('username', _username);
		sessionStorage.setItem('password', _pswd);
		sessionStorage.setItem('email', _email);
		sessionStorage.setItem('token', _token);
	}
	
	function toggleLogin() {
		_login = !_login;
	}

    onMount(() => {
        // might not need
    })
</script>

<h1 class="header">Open Source <br> Security System</h1>

{#if _login == true}
	<div class="login-container">
		<div class="login-box">
			<h2 style="font-size: 180%">Login</h2>
		</div>
		<div class="login-box">
			<p>
				<b>Username: </b>&ensp;
				<input bind:value={_username} class="input-box"
					placeholder="Enter Username"/>
			</p>
			<p>
				<b>Password: </b>&ensp;
				<input type="password" bind:value={_pswd}
					class="input-box" placeholder="Enter Password" />
			</p>
			{#if _approved == false}
				<p style="color: red;">Invalid username or password</p>
			{/if}
			<button onclick={signIn} style="padding: 6px;">Submit</button>	
		</div>
		<div style="text-align: left; padding: 12px 4px">
			<button onclick={toggleLogin}>Create New Profile</button>
		</div>
	</div>
{:else}
	<div class="login-container">
		<div class="login-box">
			<h2 style="font-size: 180%">Create Profile</h2>
		</div>
		<div class="login-box">
			<p>
				<b>Username: </b>&ensp;
				<input bind:value={_username} class="input-box"
					placeholder="Enter Username"/>
			</p>
			{#if _username != '' && (_username.length < 6 || _username.length > 12)}
				<p style="color: red;">Username must be between 6 and 12 characters</p>
			{/if}
			<p>
				<b>Password: </b>&ensp;
				<input type="password" bind:value={_pswd}
					class="input-box" placeholder="Enter Password" />
			</p>
			<p>
				<b>Confirm Password: </b>&ensp;
				<input type="password" bind:value={_confirm_pswd}
					class="input-box" placeholder="Reenter Password" />
			</p>
			{#if _pswd != _confirm_pswd && _confirm_pswd != ''}
				<p style="color: red;">Passwords must match</p>
			{/if}
			<p>
				<b>Email: </b>&ensp;
				<input bind:value={_email}
					class="input-box" placeholder="Enter Email Address" />
			</p>
			{#if _email != '' && (!_email.includes("@") || !_email.includes("."))}
				<p style="color: red;">Invalid email address</p>
			{/if}
			<button onclick={createProfile} style="padding: 6px;">Submit</button>
		</div>
	</div>
{/if}

<style>
    .header {
		font-size: 275%;
		text-align: center;
		font-family: Arial;
		color: white;
		background-color: #26355a;
		padding: 10px;
		box-shadow: 0 2px 6px rgba(0,0,0,0.15);
	}

	.login-container {
		position: absolute;
		top: 50%;
		left: 50%;
		transform: translate(-50%, -50%);
		display: flex;
		flex-direction: column;
		justify-content: center;
		text-align: center;
	}
	
	.login-box {
		text-align: center;
		justify-content: center;
		align-items: center;
		width: 350px;
		border: 1px solid black;
		padding: 10px;
		box-shadow: 0 2px 6px rgba(0,0,0,0.15);
	}

	.input-box{
		border-radius: 0.9rem;
		border: 1px solid black;
		padding: 6px;
	}
</style>