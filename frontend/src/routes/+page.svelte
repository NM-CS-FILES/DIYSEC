<script lang="ts">
    import { onMount } from "svelte";

    let src: string = "";
    let ws: WebSocket | null = null;

    onMount(() => {
        ws = new WebSocket("ws://localhost:8888/stream/1");
        ws.binaryType = "arraybuffer";

        ws.onmessage = (evt: MessageEvent<ArrayBuffer>) => {
            const blob = new Blob([evt.data], { type: "image/jpeg" });
            const url = URL.createObjectURL(blob);
            src = url;

            setTimeout(() => URL.revokeObjectURL(url), 500);
        }
    })
</script>

<style>
    img {
        width: 100%;
        object-fit: contain;
    }
</style>

<img {src} alt = "ALTERNATE"/>