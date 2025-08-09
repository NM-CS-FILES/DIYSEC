<script lang="ts">
	import { Button } from "$lib/components/ui/button/index";
	import * as Card from "$lib/components/ui/card/index";
    import * as Dialog from "$lib/components/ui/dialog/index";
	import { Input } from "$lib/components/ui/input/index";
	import { Label } from "$lib/components/ui/label/index";

    import { Session } from "$lib/session";
    import { goto } from "$app/navigation";

	const id = $props.id();

    let username = $state("");
    let password = $state("");
    let confirmedPassword = $state("");

    let dialogShow = $state(false);
    let dialogContent = $state("");
    let dialogTitle = $state("");

    function tryRegister(event: MouseEvent): void {
        if (password !== confirmedPassword) {
            dialogTitle = "Invalid Password"
            dialogContent = "Passwords Do Not Match";
            dialogShow = true;
            return;
        }

        Session.register(username, password).then(() => {
            if (Session.isAuthenticated()) {
                goto("/dashboard");
            } else {
                dialogTitle = "Invalid Registration";
                dialogContent = "Unable To Register New Account";
                dialogShow = true;
            }
        });
    }
</script>

<Dialog.Root bind:open={dialogShow}>
  <Dialog.Content>
    <Dialog.Header>
      <Dialog.Title>{dialogTitle}</Dialog.Title>
      <Dialog.Description>
        {dialogContent}
      </Dialog.Description>
    </Dialog.Header>
  </Dialog.Content>
</Dialog.Root>

<Card.Root class="mx-auto w-full max-w-sm">
	<Card.Header>
		<Card.Title class="text-2xl">Register</Card.Title>
	</Card.Header>
	<Card.Content>
		<div class="grid gap-4">
			<div class="grid gap-2">
				<Label for="username-{id}">Username</Label>
				<Input bind:value={username} id="username-{id}" type="text" required />
			</div>
			<div class="grid gap-2">
				<div class="flex items-center">
					<Label for="password-{id}">Password</Label>
				</div>
				<Input bind:value={password} id="password-{id}" type="password" required />
			</div>
            <div class="grid gap-2">
				<div class="flex items-center">
					<Label for="password-{id}">Confirm Password</Label>
				</div>
				<Input bind:value={confirmedPassword} id="password-{id}" type="password" required />
			</div>
			<Button onclick={tryRegister} type="submit" class="w-full">Register</Button>
		</div>
	</Card.Content>
</Card.Root>
