<script>
  import SkipToMap from "../components/SkipToMap.svelte";
  import Button from '../components/Button.svelte';

  export let goToNextView;
  export let skipToMap;
</script>

<div class="flex flex-col py-8 px-6 bg-[#BAFF7F] space-y-6">
  <SkipToMap skipToMap={skipToMap} customClass="text-black"/>

  <!-- Title -->
  <div class="text-4xl">
    Recommendations in mind before playing
  </div>

  <!-- Bullet points -->
  <ul class="list-disc list-inside space-y-2 text-lg font-mono">
    <li>Treat each game piece with delicacy and care 💝</li>
    <li>Always play on top of the board 🙇🏽</li>
    <li>When you’re done playing, make sure to return everything to where you found it 🫡🌱</li>
    <li>Have fun and enjoy! 🙈🙉</li>
  </ul>

<!-- Bottom image and button -->
<div class="w-full flex flex-col justify-center items-stretch">
  <!-- Right-aligned image -->
  <div class="flex justify-end">
    <img 
      src="/assets/onboarding/recommendations.png"
      alt="rocas"
      class="w-48 h-auto mb-4" 
    />
  </div>

  <!-- Centered button -->
  <div class="flex justify-center">
    <button on:click={goToNextView} class="focus:outline-none">
      <Button text="OKAAAAY"/>
    </button>
  </div>
</div>

</div>
