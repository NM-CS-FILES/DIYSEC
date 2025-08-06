<script lang="ts">
    import { onMount } from "svelte";
	import { currUser } from "../stores/userStore";
    import {User} from "../lib/User";
    import { goto } from "$app/navigation";
	
	
	let _username = $state('');
	let _pswd = $state('');
	let _confirm_pswd = $state('')
	let _email = $state('')
	let _login = $state(true);
	//let _user = new User('', '', '', '');
	let _token = $state('');

	function toggleLogin() {
		_login = !_login;
	}
	function signIn() {
		if (true) {  // CONDITION NEEDS TO BE CHANGED!
			// get authentication token and email
			storeUser();
			goto("./dashboard");
		}
	}
	function storeUser() {
		sessionStorage.setItem('username', _username);
		sessionStorage.setItem('password', _pswd);
		sessionStorage.setItem('email', _email);
		sessionStorage.setItem('token', _token);
	}
	function createProfile() {
		
		if (checkPswd()) {   // keep here?
			// FILL IN.... (POST method for sending account to server {maybe add conditions})
			_login = true;
		}
		else {
			alert("Password and confirm password do not match.")
		}
		
	}
	function checkPswd() {
		if (_pswd != _confirm_pswd) {  // If Password confirmation does not match
			return false;
		}
		_username = '';	_pswd = '';	_confirm_pswd = '';
		return true;  // should get edited for conditions
	}

	

    onMount(() => {
        
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