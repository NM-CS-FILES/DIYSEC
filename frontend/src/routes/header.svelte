<script>
	let isOpen = $state(false);
	let page = $state("Testing");

	function toggleMenu() {
		isOpen = !isOpen;
	}
	function logout() {
		// NEEDS ATTENTION!
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
		position: left;
		top: 40px;
		right: 0;
		background: white;
		border: 1px solid #ccc;
		padding: 0.5rem;
		box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
	}
	
	#header {
		width: 100%;
		height: 6%;
		display: flex;
		justify-content: space-between;
		border-bottom: 2px solid black;
		
	}
	
	.logout {
		padding: 10px;
		position: relative;
	}
</style>


<div id="header">
	<div><button class="menu-button" onclick={toggleMenu}>
	<div class="bar"></div><div class="bar"></div><div class="bar"></div>
</button></div>
	<div><h1 style="margin: auto;">{page}</h1></div>
	<div><button class="logout" onclick={logout}>Logout</button></div>
</div>
{#if isOpen}
	<div class="menu">
		<ul>
			<a href="/home">Home</a><br>
			<a href="/about">About</a><br>
			<a href="/settings">Settings</a><br>
		</ul>
	</div>
{/if}