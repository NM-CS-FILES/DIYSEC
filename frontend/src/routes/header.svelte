<script>
	import { goto } from "$app/navigation";

	let isOpen = $state(false);
	let { page } = $props();

	function toggleMenu() {
		isOpen = !isOpen;
	}
	function changeToAccount() {
		goto("./UserInfo")
	}
	function changeToDashboard() {
		goto("./dashboard");
	}
	function changeToRec() {
		goto("./Recording")
	}
	function logout() {
		// end authentication and connection from server?
		sessionStorage.clear();
		goto("./")
	}
</script>

<style>
	.menu-button {
		width: 34px;
		height: 32px;
		display: flex;
		flex-direction: column;
		justify-content: space-around;
		align-items: center;
	}

	.bar {
		width: 26px;
		height: 4px;
		background-color: #333;
		transition: all 0.3s ease;
		border-radius: 30px;
	}

	.menu {
		width:45%;
		position: left;
		top: 40px;
		right: 0;
		background: white;
		border: 1px solid #ccc;
		padding: 0.5rem;
		box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
		z-index: 10;
	}
	
	#header {
		width: 100%;
		height: 7%;
		display: flex;
		justify-content: space-between;
		border-bottom: 2px solid black;
		
	}
	
	.logout {
		padding: 7px;
		position: relative;
		margin: auto;
	}
	.page-link {
		font-size: 125%;
		cursor: pointer;
		border-bottom: 1px solid rgba(0, 0, 0, 0.788);
		padding: 6px;
	}
</style>


<div id="header">
	<div>
		<button class="menu-button" onclick={toggleMenu}>
			<div class="bar"></div><div class="bar"></div><div class="bar"></div>
		</button>
	</div>
	<div><h1 style="margin: auto;">{page}</h1></div>
	<div><button class="logout" onclick={logout}>Logout</button></div>
</div>
{#if isOpen}
	<div class="menu">
			<div class="page-link" onclick={changeToDashboard}>
				Dashboard
			</div>
			<div class="page-link" onclick={changeToRec}>
				Recordings
			</div>
			<div class="page-link" onclick={changeToAccount}>
				Account
			</div>
	</div>
{/if}
<br><br><br>