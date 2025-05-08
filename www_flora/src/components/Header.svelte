<script>
  export let title = "App Title";
  export let onMenuClick = () => {console.log('click menu')}; // Function to handle menu click
</script>

<header class="mobile-header">
  <div class="title">
    <h1>{title}</h1>
  </div>
  <button class="menu-button" on:click={onMenuClick} aria-label="Toggle menu">
    <div class="hamburger">
      <span></span>
      <span></span>
      <span></span>
    </div>
  </button>
</header>

<style>
  .mobile-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 0.5rem 1rem;
    background-color: transparent;
    color: #333;
    height: 60px;
  }

  .title h1 {
    margin: 0;
    font-size: 1.25rem;
    font-weight: 600;
  }

  .menu-button {
    background: none;
    border: none;
    cursor: pointer;
    padding: 0.5rem;
  }

  .hamburger {
    display: flex;
    flex-direction: column;
    justify-content: space-between;
    height: 20px;
    width: 24px;
  }

  .hamburger span {
    display: block;
    height: 3px;
    width: 100%;
    background-color: #333;
    border-radius: 2px;
  }
</style>
