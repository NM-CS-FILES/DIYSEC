<script lang="ts">
    import { onMount } from "svelte";
    import { Camera } from "$lib/camera";

    //

    export let camera: Camera;
    let src: string = ""

    //

    onMount(() => {
        camera.ws!.onmessage = (evt: MessageEvent<ArrayBuffer>) => {
            const blob = new Blob([evt.data], { type: "image/jpeg" });
            const url = URL.createObjectURL(blob);
            src = url;
            setTimeout(() => URL.revokeObjectURL(url), 500);
        }
        
    })
</script>

<img {src} alt = "No Camera Data"/>

<style>
    img {
        width: 30%;
        object-fit: contain;
    }
</style>