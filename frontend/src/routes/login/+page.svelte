<script lang="ts">
    import { goto } from "$app/navigation";
	import LoginForm from "./login-form.svelte";
    import { Session } from "$lib/session";
    import { onMount } from "svelte";

    onMount(() => {
        if (Session.isAuthenticated()) {
            goto("/dashboard");
        }
    });
</script>

<div class="flex h-screen w-full items-center justify-center px-4">
	<LoginForm/>
</div>
