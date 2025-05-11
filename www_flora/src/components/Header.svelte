<script>
  import Menu from './Menu.svelte';

  let showMenu = false;

  function handleRefresh() {
    window.location.reload();
  }

  function onMenuClick() {
    showMenu = true;
  }

  function handleMenuClose() {
    showMenu = false;
  }
</script>

<header class="mobile-header p-5 flex justify-between">
  <div class="cursor-pointer title" on:click={handleRefresh}>
    <img src="assets/header/logo.png" alt="App Logo" class="h-[60px]" />
  </div>
  <button class="menu-button cursor-pointer" on:click={onMenuClick} aria-label="Toggle menu">
    <img src="assets/header/menu_icon.png" alt="hamburguer" />
  </button>
</header>

{#if showMenu}
  <Menu on:close={handleMenuClose} />
{/if}
