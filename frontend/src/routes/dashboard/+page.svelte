<script lang="ts">
    import * as Nav from "$lib/components/ui/navigation-menu/index"
</script>

<div class="nav-div">
    <Nav.Root>
      <Nav.List>
        <Nav.Item>
            <Nav.Link href="/dashboard">Dashboard</Nav.Link>
        </Nav.Item>
        <Nav.Item>
            <Nav.Link href="/about">About</Nav.Link>
        </Nav.Item>
        <Nav.Item>
            <Nav.Link href="/recordings">Recordings</Nav.Link>
        </Nav.Item>
      </Nav.List>
    </Nav.Root>
</div>

<style>
    .nav-div {
        display: flex;
    }
</style>