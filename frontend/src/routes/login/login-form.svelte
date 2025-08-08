<script lang="ts">
    import { goto } from "$app/navigation";
	import * as Card from "$lib/components/ui/card/index.js";
	import * as Dialog from "$lib/components/ui/dialog/index";
    import { Button } from "$lib/components/ui/button/index.js";
	import { Input } from "$lib/components/ui/input/index.js";
	import { Label } from "$lib/components/ui/label/index.js";


    import { Session } from "$lib/session";

	const id = $props.id();

    let dialogShow = $state(false);
    let username = $state("");
    let password = $state("");

    function tryLogin(event: MouseEvent): void {
        Session.login(username, password).then(() => {
            if (Session.isAuthenticated()) {
                goto("/dashboard");
            } else {
                dialogShow = true;
            }
        });
    }
</script>

<Dialog.Root bind:open={dialogShow}>
  <Dialog.Content>
    <Dialog.Header>
      <Dialog.Title>Invalid Login</Dialog.Title>
      <Dialog.Description>
        An Incorrect Username Or Password Has Been Entered
      </Dialog.Description>
    </Dialog.Header>
  </Dialog.Content>
</Dialog.Root>

<Card.Root class="mx-auto w-full max-w-sm">
	<Card.Header>
		<Card.Title class="text-2xl">Login</Card.Title>
		<Card.Description>Enter your username below to login to your account</Card.Description>
	</Card.Header>
	<Card.Content>
		<div class="grid gap-4">
			<div class="grid gap-2">
				<Label for="username-{id}">Username</Label>
				<Input bind:value={username} id="username-{id}" type="text" placeholder="username" required />
			</div>
			<div class="grid gap-2">
				<div class="flex items-center">
					<Label for="password-{id}">Password</Label>
				</div>
				<Input bind:value={password} id="password-{id}" type="password" required />
			</div>
			<Button onclick={tryLogin} type="submit" class="w-full">Login</Button>
		</div>
	</Card.Content>
</Card.Root>
