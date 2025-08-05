<script lang="ts">
	import { Recording } from "../../lib/recording"
	let totalRecs = $state(7);
	
	let recordings: Recording[] = [];
	let customRecording = $state(false);
	let viewRecording = $state(false);
	let customTime = $state('');
	let customDate = $state('');
	let customDuration = $state('');
	let customCamID = $state('');

	function toggleCustom() {
		customRecording = !customRecording;
	}
	function toggleView() {
		viewRecording = !viewRecording;
	}
	function submit() {
		// Add POST functionality (customDuration cast to an int??)
		customTime = ''; customDate = ''; customDuration = ''; customCamID = '';
	}

	for (let i = 0; i < totalRecs; i++) {   // NEEDS EDITING FOR INTEGRATION
		let y = new Recording(i, "07/31/24", 1, "10:00pm");
		y.setCameraID(i);
		recordings.push(y);
	}
</script>

<style>
	.drop-down {
		width: 100%;
		role: button;
		border-bottom: 2px solid black;
		border-left: 2px solid black;
		border-right: 2px solid black;
		padding: 16px;
		font-size: 125%;
	}
	.custom-categories {
		display: flex;
		
		width: 100%;
		border-bottom: 1px solid black;
		padding: 10px;
	}

	.rec-display{
		display: flex;
		flex-wrap: wrap;
		gap: 1.4rem;
	}

	.rec-item {
		width: 300px;
		border: 1px solid black;
	}
</style>

<div class="drop-down" onclick={toggleCustom}><b>Make Custom Recording</b></div>
{#if customRecording == true}
	<div class="custom-categories">
		Date (as numbers mm/dd/yyyy): &emsp;
		<input style="align-self: center;" bind:value={customDate} />
	</div>
	<div class="custom-categories">
		Time (hh/mm): &emsp; 
		<input style="align-self: center;" bind:value={customTime} />
	</div>
	<div class="custom-categories">
		Duration (in minutes): &emsp;
		<input style="align-self: center;" bind:value={customDuration} />
	</div>
	<div class="custom-categories">
		Camera ID: &emsp;
		<input style="align-self: center;" bind:value={customCamID} />
	</div>
	<br>
	<div style="text-align: center;"><button onclick={submit} style="padding: 8px; text-align: center;">Submit</button></div>
	<br><br>
{/if}

<div class="drop-down" onclick={toggleView}><b>View Saved Recording</b></div>
{#if viewRecording == true}
	<div class="rec-display">
		{#each recordings as recording}
			<div class="rec-item">
				<video src={recording.getRecording()} controls>
					<track kind="captions">
				</video>
				<b>Date: </b> {recording.getDate}
				<b>Time: </b> {recording.getTime}
				<b>Camera: </b> {recording.getCameraID}
			</div>
		{/each}
	</div>
{/if}