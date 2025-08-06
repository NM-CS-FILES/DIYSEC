<script lang="ts">
    import { onMount } from "svelte";
	//import { goto } from "$app/navigation";
	import {User} from "../../lib/User";
	
	
  	let unPopup = $state(false);  // un = username
	let pwPopup = $state(false);  // pw = password
	let emPopup = $state(false);  // em = email
	
	let user = new User('', '', '', '');
    
    let username = $state('');
	let password = $state('');
    let hiddenPswd = $state('');
	let email = $state('');
    let token = $state('');

  	const changeUn = () => unPopup = !unPopup;
	const changePw = () => pwPopup = !pwPopup;
	const changeEm = () => emPopup = !emPopup;
	
	function updateProfile() {  // updates the DB on the server
		user.setUsername(username);
		user.setPassword(password);
		user.setEmail(email);
        storeUser();
        hiddenPswd = hidePswd();
		// add POST methods
		unPopup = false; pwPopup = false; emPopup = false;
	}
    function hidePswd() {
        let temp = '';
        for (let i = 0; i < password.length; ++i) {
            temp += '*';
        }
        return temp;
    }
    function storeUser() {
		sessionStorage.setItem('username', username);
		sessionStorage.setItem('password', password);
		sessionStorage.setItem('email', email);
		sessionStorage.setItem('token', token);
	}
	onMount(() => {
		user.setUsername(sessionStorage.getItem('username')!);
    	user.setPassword(sessionStorage.getItem('password')!);
    	user.setEmail(sessionStorage.getItem('email')!);
    	user.setToken(sessionStorage.getItem('token')!);
		username = user.getUsername();
		password = user.getPassword();
    	hiddenPswd = hidePswd();
		email = user.getEmail();
    	token = user.getToken();
	})
</script>

<style>
	.container {
		position: absolute;
		top: 50%;
		left: 50%;
		transform: translate(-50%, -50%);
		display: flex;
		flex-direction: column;
		justify-content: center;
		text-align: center;
	}
	
	.info-box {
		display: flex;
		text-align: center;
		justify-content: center;
		align-items: center;
		border: 1px solid black;
		padding: 10px 30px;
		box-shadow: 0 2px 6px rgba(0,0,0,0.15);
	}

	.input-box{
		border-radius: 0.9rem;
		border: 1px solid black;
		padding: 6px;
	}

	.outer-popup {
    position: fixed;
    top: 0; left: 0;
    width: 100vw; height: 100vh;
    background: rgba(0, 0, 0, 0.5);
    display: flex; justify-content: center; align-items: center;
    z-index: 10;
  }

  .inner-popup {
    background: white;
    padding: 2rem;
    border-radius: 8px;
    box-shadow: 0 0 10px rgba(0,0,0,0.3);
    min-width: 300px;
  }

	h3 { text-align: center; }

	
	p { text-align:left; }
</style>

<div class="container">
	<div class="info-box">
		<h2>Account Information</h2>
	</div>
	<div class="info-box" style="justify-content:space-between">
		<p>Username: {username}</p>&emsp; <!-- &emsp is used for extra spacing -->
		<button on:click={changeUn}>Change</button>
	</div>
	<div class="info-box" style="justify-content:space-between">
		<p>Password: {hiddenPswd}</p>&emsp;
		<button on:click={changePw}>Change</button>
	</div>
	<div class="info-box" >
		<p>Email: {email}</p>&emsp;
		<button on:click={changeEm}>Change</button>
	</div>
	
</div>

{#if unPopup == true}
	<div class="outer-popup" on:click={changeUn}>
    <div class="inner-popup" on:click|stopPropagation>
      <h3>Change Username</h3>
			New Username: &emsp;
			<input class="input-box" bind:value={username} />
			<br>
      <button on:click={updateProfile}>Update</button>
    </div>
  </div>
{:else if pwPopup == true}
	<div class="outer-popup" on:click={changePw}>
    <div class="inner-popup" on:click|stopPropagation>
      <h3>Change Password</h3>
			New Password: &emsp;
			<input type="password" class="input-box" bind:value={password} />
			<br>
      <button on:click={updateProfile}>Update</button>
    </div>
  </div>
{:else if emPopup == true}
	<div class="outer-popup" on:click={changeEm}>
    <div class="inner-popup" on:click|stopPropagation>
      <h3>Change Email</h3>
			New Email: &emsp;
			<input class="input-box" bind:value={email} />
			<br>
      <button on:click={updateProfile}>Update</button>
    </div>
  </div>
{/if}