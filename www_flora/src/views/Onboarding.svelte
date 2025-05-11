<script>
  import { goto } from "$app/navigation";
  import SkipToMap from "../components/SkipToMap.svelte";

  export let goToNextView;
  export let skipToMap;
  export let currentView;

  const content = {
    'onboarding1': {
      'title': 'Flora is an ecosystem in crisis',
      'subtitle': 'It has lost its joy and suddenly, everything is dark, silent, and motionless. A curse has fallen upon the electronic garden.',
      'bgColor': 'bg-[#1C0405]'
    },
    'onboarding2': {
      'title': 'With you, the garden blooms again',
      'subtitle': 'Like any garden, Flora requires specific care, which you must decipher by observing closely and with curiosity.',
      'bgColor': 'bg-[#5DAC7E]',
    },
    'onboarding3': {
      'title': 'Become part of Flora\'s ecosystem',
      'subtitle': 'Helping the other species recover and thus restore the natural cycle so everything can once again function in harmony.',
      'bgColor': 'bg-[#A75CC0]'
    }
  }
</script>

<div class={`w-screen h-full ${content[currentView].bgColor} flex flex-col items-center`}>
    <SkipToMap skipToMap={skipToMap} customClass="text-white"/>

  <div class="flex flex-col items-center p-4 gap-0">
    <div class="relative w-full">
      <img
        src={`/assets/onboarding/${currentView}/bg_a.png`}
        alt="bg_a"
        class="w-full h-auto"
      />
      <img
        src={`/assets/onboarding/${currentView}/il.png`}
        alt="il"
        class="absolute inset-0 w-full h-auto"
      />
    </div>
    <div class="relative w-full">
    <img
      src={`/assets/onboarding/${currentView}/bg_b.png`}
      alt="bg_b"
      class="w-full h-auto"
    />
    <div class="absolute inset-0 w-full h-auto pt-15 pl-8 pr-4">
      <div class="text-4xl">{content[currentView].title}</div>
      <br>
      <div class="font-mono">{content[currentView].subtitle}</div>
    </div>
    </div>
  </div>

    <div class="relative w-full h-full flex justify-end items-end p-8">
      <button on:click={goToNextView} class="absolute bottom-12 right-10">
        <img
          src="/assets/buttons/arrow.png"
          alt="arrow"
          class="w-[70px] h-auto"
        />
      </button>
    </div>
</div>
