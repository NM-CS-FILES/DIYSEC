<script lang="ts">
    import { Session } from "$lib/session";
    import { onMount } from "svelte";
    import { goto } from "$app/navigation";

    onMount(() => goto(Session.isAuthenticated() ? "/dashboard" : "/login"));
</script>