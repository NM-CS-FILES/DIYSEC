<script lang="ts">
	import { Camera } from "../../lib/camera2";
	let totCams = $state(8);

	let cameras: Camera[] = [];

	for (let i = 0; i < totCams; i++) {  // NEEDS EDITING FOR INTEGRATION
		let x = new Camera(i);
		// x.lastFrame = "https://images.app.goo.gl/ShJRXPTE8FZifr8F9";
		x.lastFrame = "";
		cameras.push(x);
	}
</script>

<style>
	.camera-grid {
		display: grid;
		grid-template-columns: repeat(auto-fit, minmax(350px, 1fr));
		gap: 1rem;
	}
	.camera-tile {
		border: 1px solid #ccc;
		border-radius: 8px;
		overflow: hidden;
		background: #000;
		color: white;
		padding: 0.5rem;
	}
	img {
		width: 100%;
		height: auto;
	}
</style>

<div class="camera-grid">
	{#each cameras as camera}
		<div class="camera-tile">
			<img src={camera.lastFrame} alt="Camera Icon" />
			<p style="text-align:center">ID: {camera.camID}</p>
		</div>
	{/each}
</div>